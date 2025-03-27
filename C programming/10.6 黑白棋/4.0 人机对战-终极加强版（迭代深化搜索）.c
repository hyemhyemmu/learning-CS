#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lab8part2.h"
#define UNOCCUPIED 'U'
#define BLACK 'B'
#define WHITE 'W'
#define MAX_DEPTH 8  // maximum search depth for Iterative Deepening
#define TIME_LIMIT 1.8 // time limit for searching. a 0.2s buff time is added
#define CACHE_SIZE 10007 

/**
 * @name the Reversi game/ Othello
 * @author Fei Mo
 * @date 2025-03-26
 * @brief The game is equipped with a STRONG AI player.
 * @details The main idea of the AI is Iterative Deepening Alpha-Beta Pruning with Transposition Table.
 * In case of timeout, a clock is set and the search depth is dynamically adjusted.
 */

// global variables
unsigned long long lastHash = 0;
int lastScore = 0;

// for sorting. 
// This should be in the header file, but for submission clarity, it is placed here.
typedef struct {
    int row;
    int col;
    int score;
} Move;

// structure of the transposition table - for caching search results
typedef struct {
    unsigned long long hash;  // Zobrist hash of board position
    int depth;               // search depth for this result
    int score;               // evaluation score
    int bestRow;             // best move row
    int bestCol;             // best move column
} TranspositionEntry;

// global optimizing structure initialization
TranspositionEntry transTable[CACHE_SIZE];
clock_t searchStart;
int searchAbort;

// static weight matrix for board position evaluation
// - set to 8*8 as required by the problem
// - figures are chosen based on the general strategy of Reversi:
//  - corners are the most valuable, followed by edges, and then the rest
// other than that, the numbers are chosen arbitrarily, just to show the idea
static int weightTable[8][8] = {
    {100, -20, 10, 5, 5, 10, -20, 100},
    {-20, -50, -2, -2, -2, -2, -50, -20},
    {10, -2, 8, 1, 1, 8, -2, 10},
    {5, -2, 1, 1, 1, 1, -2, 5},
    {5, -2, 1, 1, 1, 1, -2, 5},
    {10, -2, 8, 1, 1, 8, -2, 10},
    {-20, -50, -2, -2, -2, -2, -50, -20},
    {100, -20, 10, 5, 5, 10, -20, 100}
};

// function prototypes
bool positionInBounds(int n, int row, int col);
bool checkValidMove(const char board[][26], int n, char color, int row, int col);
void boardConfigurations(char board[][26], int n);
void InitializeBoard(char board[][26], int n);
void printAvailableMoves(char board[][26], int n, char color);
void doMove(char board[][26], int n, char color, int row, int col);
int countFlips(const char board[][26], int n, char color, int row, int col);
bool hasValidMove(const char board[][26], int n, char color);
void getComputerMove(char board[][26], int n, char computerColor, int *row, int *col);
void playGame(char board[][26], int n, char computerColor);
char getWinner(const char board[][26], int n);
int findBestMove(const char board[][26], int n, char turn, int *row, int *col, int depth);
int minimax(char board[][26], int n, char turn, int depth, int alpha, int beta, bool isMaximizing);
int evaluateBoard(const char board[][26], int n, char turn);
void copyBoard(const char source[][26], char dest[][26], int n);
bool hasAnyValidMove(const char board[][26], int n, char color);
char getOpponent(char color);
bool isStablePiece(const char board[][26], int n, int row, int col);

// main function
int main(){
    int dimension;
    printf("Enter the board dimension: ");
    scanf("%d", &dimension);
    char board[26][26];
    char computerColor;
    
    printf("Computer plays (B/W) : ");
    scanf(" %c", &computerColor);
    
    InitializeBoard(board, dimension);
    printBoard(board, dimension);
    
    // main game logic
    playGame(board, dimension, computerColor);
    
    return 0;
}



// functions

// compare moves' score
int compareMoves(const void *a, const void *b) {
    return ((Move*)b)->score - ((Move*)a)->score;
}

// only copy n characters & use memcpy are all for save of memeory and time
void copyBoard(const char source[][26], char dest[][26], int n) {
    for (int i = 0; i < n; i++) {
        memcpy(dest[i], source[i], (size_t)n); 
    }
}

// Pre-generate a list of valid moves
void getValidMoves(const char board[][26], int n, char turn, Move moves[], int *moveCount) {
    *moveCount = 0;
    char nonConstBoard[26][26];
    copyBoard(board, nonConstBoard, n);
    
    // First pass: collect CORNER moves - highest priority
    for (int r = 0; r < n; r += n-1) {
        for (int c = 0; c < n; c += n-1) {
            if (checkValidMove(board, n, turn, r, c)) {
                moves[*moveCount].row = r;
                moves[*moveCount].col = c;
                moves[*moveCount].score = 9999; // highest score for corners
                (*moveCount)++;
            }
        }
    }
    
    // Second pass: collect edge moves - second highest priority
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if ((r == 0 || r == n-1 || c == 0 || c == n-1) && 
                !((r == 0 || r == n-1) && (c == 0 || c == n-1))) { // exclude corners
                if (checkValidMove(board, n, turn, r, c)) {
                    moves[*moveCount].row = r;
                    moves[*moveCount].col = c;
                    // edge position score + number of flips
                    moves[*moveCount].score = 500 + countFlips(board, n, turn, r, c) * 10;
                    (*moveCount)++;
                }
            }
        }
    }
    
    // Third pass: collect other positions
    for (int r = 1; r < n-1; r++) {
        for (int c = 1; c < n-1; c++) {
            if (checkValidMove(board, n, turn, r, c)) {
                moves[*moveCount].row = r;
                moves[*moveCount].col = c;
                
                // X position penalty 
                // note: all the figures are just arbitrary chosen, to indicate relative values
                int posScore = 0;
                if ((r == 1 && c == 1) || (r == 1 && c == n-2) || 
                    (r == n-2 && c == 1) || (r == n-2 && c == n-2)) {
                    if (board[r-(r==1?1:-1)][c-(c==1?1:-1)] == UNOCCUPIED) {
                        posScore = -200;
                    }
                }
                
                // position score + number of flips + position weight
                moves[*moveCount].score = posScore + countFlips(board, n, turn, r, c) * 5;
                (*moveCount)++;
            }
        }
    }
    
    // sort by score - really handy to use qsort
    qsort(moves, (size_t)(*moveCount), sizeof(Move), compareMoves);
    
    // limit the number of moves processed - don't want timeout
    *moveCount = (*moveCount > 12) ? 12 : *moveCount;
}

// evaluation function for deep search
int evaluateBoardQuick(const char board[][26], int n, char turn) {
    char nonConstBoard[26][26];
    copyBoard(board, nonConstBoard, n);
    
    char opponent = getOpponent(turn);
    int score = 0;
    int myCount = 0, opponentCount = 0;
    
    // calculate quick hash value
    int currentHash = 0;
    for (int i = 0; i < 4 && i < n; i++) {
        currentHash = (currentHash << 4) | (nonConstBoard[i][i] == turn ? 1 : (nonConstBoard[i][i] == opponent ? 2 : 0));
        currentHash = (currentHash << 4) | (nonConstBoard[n-1-i][i] == turn ? 1 : (nonConstBoard[n-1-i][i] == opponent ? 2 : 0));
    }
    
    // cache hit! save lots of time
    if (currentHash == lastHash) {
        return lastScore;
    }
    
    // quick position scoring
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (nonConstBoard[r][c] == turn) {
                myCount++;
                // corners
                if ((r == 0 || r == n-1) && (c == 0 || c == n-1)) {
                    score += 600; // make the score BIG
                } 
                // edges
                else if (r == 0 || r == n-1 || c == 0 || c == n-1) {
                    score += 70;
                }
                // X position penalty
                else if (((r == 1 && c == 1) || (r == 1 && c == n-2) || 
                         (r == n-2 && c == 1) || (r == n-2 && c == n-2)) &&
                         nonConstBoard[r-(r==1?1:-1)][c-(c==1?1:-1)] == UNOCCUPIED) {
                    score -= 200; // can be higher if really dislike X positions, just the choice of strategy
                }
            } else if (nonConstBoard[r][c] == opponent) {
                opponentCount++;
                // reverse scoring for opponent positions
                if ((r == 0 || r == n-1) && (c == 0 || c == n-1)) {
                    score -= 600;
                } 
                else if (r == 0 || r == n-1 || c == 0 || c == n-1) {
                    score -= 70;
                }
            }
        }
    }
    
    // piece count difference is important in endgame!
    // this can be changed as well. just a choice of strategy.
    // I hardcoded here to make the score BIG, but can be adjusted
    int totalPieces = myCount + opponentCount;
    double fillRate = (double)totalPieces / (n * n);
    if (fillRate > 0.8) { 
        score += (myCount - opponentCount) * 100;
    }
    
    // update cache
    lastHash = currentHash;
    lastScore = score;
    
    return score;
}

// get more accurate search depth but reduce max depth to improve speed
// this dynamically adjusts the search depth based on the board position
// this is a KEY optimization in the whole programming
// make the whole process highly effective. absolutely better than just hardcoded a depth
int getSearchDepth(const char board[][26], int n) {
    int emptyCount = 0;
    for (int r = 0; r < n; r++) 
        for (int c = 0; c < n; c++) 
            emptyCount += (board[r][c] == UNOCCUPIED);
    
    // optimize endgame search depth
    if (emptyCount <= 8) {
        return (emptyCount <= 5) ? 7 : 6; // control max depth
    }
    
    // adjust phase division
    double fillRate = (double)(n*n - emptyCount) / (n*n);
    return fillRate < 0.5 ? 3 : 4; 
}

// quick Zobrist hash calculation function
unsigned long long getZobristHash(const char board[][26], int n) {
    unsigned long long hash = 0;
    static unsigned long long zobristTable[26][26][3]; // 3 states: empty, black, white
    static int initialized = 0;
    
    // initialize Zobrist table (only once)
    if (!initialized) {
        srand((unsigned int)time(NULL));
        for (int r = 0; r < 26; r++) {
            for (int c = 0; c < 26; c++) {
                for (int p = 0; p < 3; p++) {
                    zobristTable[r][c][p] = ((unsigned long long)rand() << 32) | rand();
                }
            }
        }
        initialized = 1;
    }
    
    // calculate hash value for current board
    // note: this is actually the reason why i use Zoobrist's. The XOR just make everything so efficient
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (board[r][c] == BLACK) {
                hash ^= zobristTable[r][c][1];
            } else if (board[r][c] == WHITE) {
                hash ^= zobristTable[r][c][2];
            } else {
                hash ^= zobristTable[r][c][0];
            }
        }
    }
    
    return hash;
}

// transposition table lookup
bool probeTransTable(unsigned long long hash, int depth, int *score, int *bestRow, int *bestCol) {
    int index = hash % CACHE_SIZE;
    if (transTable[index].hash == hash && transTable[index].depth >= depth) {
        *score = transTable[index].score;
        if (bestRow) *bestRow = transTable[index].bestRow;
        if (bestCol) *bestCol = transTable[index].bestCol;
        return true;
    }
    return false;
}

// transposition table store
void storeTransTable(unsigned long long hash, int depth, int score, int bestRow, int bestCol) {
    int index = hash % CACHE_SIZE;
    if (transTable[index].depth <= depth) {
        transTable[index].hash = hash;
        transTable[index].depth = depth;
        transTable[index].score = score;
        transTable[index].bestRow = bestRow;
        transTable[index].bestCol = bestCol;
    }
}

// core evaluation function (simplified quick version)
int evaluateFast(const char board[][26], int n, char player) {
    char opponent = getOpponent(player);
    int score = 0, myMobility = 0, oppMobility = 0;
    
    for (int r = 0; r < n && r < 8; r++) {
        for (int c = 0; c < n && c < 8; c++) {
            // position value scoring
            if (board[r][c] == player) {
                score += weightTable[r < 8 ? r : 7][c < 8 ? c : 7];
            } else if (board[r][c] == opponent) {
                score -= weightTable[r < 8 ? r : 7][c < 8 ? c : 7];
            }
            
            // simple mobility calculation
            if (board[r][c] == UNOCCUPIED) {
                if (checkValidMove(board, n, player, r, c)) myMobility++;
                if (checkValidMove(board, n, opponent, r, c)) oppMobility++;
            }
        }
    }
    
    // add mobility score
    score += (myMobility - oppMobility) * 5;
    
    return score;
}

// quick move generation and sorting
void getSortedMoves(const char board[][26], int n, char player, Move moves[], int *count) {
    *count = 0;
    
    // prioritize checking corners!
    int corners[4][2] = {{0,0}, {0,n-1}, {n-1,0}, {n-1,n-1}};
    for (int i = 0; i < 4; i++) {
        int r = corners[i][0], c = corners[i][1];
        if (checkValidMove(board, n, player, r, c)) {
            moves[(*count)].row = r;
            moves[(*count)].col = c;
            moves[(*count)].score = 999999; // just make it big to prioritize corners
            (*count)++;
        }
    }
    
    if (*count > 0) return;  // best case: if there are corner moves, return immediately
    
    // generate other moves and evaluate
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (board[r][c] == UNOCCUPIED && checkValidMove(board, n, player, r, c)) {
                moves[*count].row = r;
                moves[*count].col = c;
                
                // prioritize edges
                if (r == 0 || r == n-1 || c == 0 || c == n-1) {
                    moves[*count].score = 500 + countFlips(board, n, player, r, c);
                } else {
                    int weight = r < 8 && c < 8 ? weightTable[r][c] : 0;
                    // lower priority for dangerous X positions
                    if ((r == 1 && c == 1) || (r == 1 && c == n-2) ||
                        (r == n-2 && c == 1) || (r == n-2 && c == n-2)) {
                        weight -= 100;
                    }
                    moves[*count].score = weight + countFlips(board, n, player, r, c) * 5;
                }
                (*count)++;
            }
        }
    }
    
    // quick sort again
    qsort(moves, (size_t)(*count), sizeof(Move), compareMoves);
    
    // limit the number of moves processed for efficiency - choose 16 arbitrarily
    *count = *count > 16 ? 16 : *count;
}

// Alpha-Beta core search algorithm (with transposition table)
int alphaBeta(char board[][26], int n, char player, int depth, int alpha, int beta, int *bestRow, int *bestCol) {
    // check time limit
    if ((clock() - searchStart) * 1.0 / CLOCKS_PER_SEC > TIME_LIMIT) {
        searchAbort = 1;
        return 0;
    }
    
    char opponent = getOpponent(player);
    unsigned long long hash = getZobristHash(board, n);
    
    // transposition table lookup
    int tableScore;
    if (probeTransTable(hash, depth, &tableScore, bestRow, bestCol)) {
        return tableScore;
    }
    
    // leaf node evaluation
    if (depth == 0) {
        int score = evaluateFast(board, n, player);
        storeTransTable(hash, depth, score, -1, -1);
        return score;
    }
    
    Move moves[64];
    int moveCount;
    getSortedMoves(board, n, player, moves, &moveCount);
    
    // no valid moves
    if (moveCount == 0) {
        // check if opponent also has no moves
        int oppMoveCount;
        Move oppMoves[64];
        getSortedMoves(board, n, opponent, oppMoves, &oppMoveCount);
        
        if (oppMoveCount == 0) {
            // game over, calculate final score
            int myCount = 0, oppCount = 0;
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < n; c++) {
                    if (board[r][c] == player) myCount++;
                    else if (board[r][c] == opponent) oppCount++;
                }
            }
            return myCount > oppCount ? 99999 : (myCount < oppCount ? -99999 : 0); // just a arbitrary big number to indicate win
        }
        
        // opponent's turn, logic is pretty much the same
        return -alphaBeta(board, n, opponent, depth - 1, -beta, -alpha, NULL, NULL);
    }
    
    int maxScore = -999999;
    int localBestRow = -1, localBestCol = -1;
    
    // iterate through all moves
    for (int i = 0; i < moveCount; i++) {
        int row = moves[i].row;
        int col = moves[i].col;
        int flippedPositions[64][2]; // Max possible flips is 64-1
        
        // Apply move and record flipped positions
        int flipCount = applyMove(board, n, player, row, col, flippedPositions);
        
        // Recursive search
        int score = -alphaBeta(board, n, opponent, depth - 1, -beta, -alpha, NULL, NULL);
        
        // Undo the move
        undoMove(board, n, player, row, col, flippedPositions, flipCount);
        
        if (searchAbort) return 0;
        
        if (score > maxScore) {
            maxScore = score;
            localBestRow = row;
            localBestCol = col;
            
            if (score > alpha) {
                alpha = score;
                if (alpha >= beta) break; // Beta pruning
            }
        }
    }
    
    // store in transposition table
    storeTransTable(hash, depth, maxScore, localBestRow, localBestCol);
    
    if (bestRow) *bestRow = localBestRow;
    if (bestCol) *bestCol = localBestCol;
    
    return maxScore;
}

int makeMove(const char board[][26], int n, char turn, int *row, int *col) {
    // initialization
    memset(transTable, 0, sizeof(transTable));
    searchStart = clock();
    searchAbort = 0;
    
    // Only copy the board once at top level
    char tempBoard[26][26];
    memcpy(tempBoard, board, n * sizeof(tempBoard[0])); // Copy only the rows we need
    
    // iterative deepening search
    int bestScore = -999999;
    *row = -1;
    *col = -1;
    
    // first check corner positions - quick win!
    int corners[4][2] = {{0,0}, {0,n-1}, {n-1,0}, {n-1,n-1}};
    for (int i = 0; i < 4; i++) {
        int r = corners[i][0], c = corners[i][1];
        if (checkValidMove(tempBoard, n, turn, r, c)) {
            *row = r;
            *col = c;
            return 999999; // Corner is always best
        }
    }
    
    // calculate number of empty spaces to adjust search depth
    int emptyCount = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (tempBoard[r][c] == UNOCCUPIED) emptyCount++;
        }
    }
    
    // determine maximum search depth
    int maxDepth = MAX_DEPTH;
    if (emptyCount <= 10) maxDepth = 10; // deeper search for endgame! this is a key optimization!
    else if (emptyCount <= 16) maxDepth = 9;
    else maxDepth = 7;
    
    // iterative deepening search - using our optimized tempBoard
    for (int depth = 1; depth <= maxDepth && !searchAbort; depth++) {
        int currentRow = -1, currentCol = -1;
        int score = alphaBeta(tempBoard, n, turn, depth, -999999, 999999, &currentRow, &currentCol);
        
        if (!searchAbort && currentRow >= 0 && currentCol >= 0) {
            bestScore = score;
            *row = currentRow;
            *col = currentCol;
        }
        
        // if time is close to limit, exit early
        if ((clock() - searchStart) * 1.0 / CLOCKS_PER_SEC > TIME_LIMIT * 0.9) 
            break;
    }
    
    // ensure there is a valid move
    if (*row == -1 || *col == -1) {
        // if deep search fails, perform simple search
        Move moves[64];
        int moveCount;
        getSortedMoves(tempBoard, n, turn, moves, &moveCount);
        if (moveCount > 0) {
            *row = moves[0].row;
            *col = moves[0].col;
            bestScore = moves[0].score;
        }
    }
    
    return bestScore;
}

// boundary check
bool positionInBounds(int n, int row, int col) {
    return (row >= 0 && row < n && col >= 0 && col < n);
}

// [MAIN GAME]
void playGame(char board[][26], int n, char computerColor) {
    char nonConstBoard[26][26];
    copyBoard(board, nonConstBoard, n);
    
    char humanColor = (computerColor == BLACK) ? WHITE : BLACK;
    char currentPlayer = BLACK; // the example case says black always goes first
    bool gameOver = false;
    
    while (!gameOver) {
        // check if current player still able to move
        if (!hasValidMove(nonConstBoard, n, currentPlayer)) {
            // check if the other player still able to move
            char opponent = (currentPlayer == BLACK) ? WHITE : BLACK;
            if (!hasValidMove(nonConstBoard, n, opponent)) {
                // if both players cannot move, game over
                char winner = getWinner(nonConstBoard, n);
                if (winner == BLACK) {
                    printf("B player wins.\n");
                } else if (winner == WHITE) {
                    printf("W player wins.\n");
                } else {
                    printf("Draw!\n");
                }
                gameOver = true;
                break;
            } else {
                // switch turn if current player cannot move
                printf("%c player has no valid move.\n", currentPlayer);
                currentPlayer = opponent;
                continue;
            }
        }
        
        // human player's round logic
        if (currentPlayer == humanColor) {
            char row, col;
            printf("Enter move for colour %c (RowCol): ", humanColor);
            scanf(" %c%c", &row, &col);
            
            int rowIdx = row - 'a';
            int colIdx = col - 'a';
            
            if (rowIdx < 0 || rowIdx >= n || colIdx < 0 || colIdx >= n || 
                !checkValidMove(nonConstBoard, n, humanColor, rowIdx, colIdx)) {
                printf("Invalid move.\n"); // game over straight away when invalid move!
                char winner = computerColor;
                if (winner == BLACK) {
                    printf("B player wins.\n");
                } else if (winner == WHITE) {
                    printf("W player wins.\n");
                }
                gameOver = true;
                break;
            }
            
            // valid move, update the board
            doMove(nonConstBoard, n, humanColor, rowIdx, colIdx);
            printBoard(nonConstBoard, n);
            
        } else { // computer's round logic
            int row, col;
            int score = makeMove(nonConstBoard, n, computerColor, &row, &col);
            
            printf("Computer places %c at %c%c.\n", computerColor, 'a' + row, 'a' + col);
            doMove(nonConstBoard, n, computerColor, row, col);
            printBoard(nonConstBoard, n);
        }
        
        // switch turn
        currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
    }
}

// add missing getWinner function
char getWinner(const char board[][26], int n) {
    int blackCount = 0, whiteCount = 0;
    
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (board[r][c] == BLACK) blackCount++;
            else if (board[r][c] == WHITE) whiteCount++;
        }
    }
    
    if (blackCount > whiteCount) return BLACK;
    else if (whiteCount > blackCount) return WHITE;
    else return UNOCCUPIED; // Draw
}

// add missing hasValidMove function
bool hasValidMove(const char board[][26], int n, char color) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (checkValidMove(board, n, color, r, c)) {
                return true;
            }
        }
    }
    return false;
}

// as requested in the head file
void printBoard(char board[][26], int n) {
    // row tag and col tag
    // first line
    printf("  ");
    for (int i = 0; i < n; i++){
        printf("%c", 'a'+i);
    }
    printf("\n");

    // other lines
    for (int row = 0; row < n; row++) {
        printf("%c ", 'a' + row);
        for (int col = 0; col < n; col++) {
            printf("%c", board[row][col]);
        }
        printf("\n");
    }
}


void boardConfigurations(char board[][26], int n){
    printf("Enter board configuration:\n");
    char color, row, col;
    while (1){
        scanf(" %c%c%c", &color, &row, &col);
        if (color == '!' && row == '!' && col == '!'){
            break;
        }
        board[row - 'a'][col - 'a'] = color;  
    }
    printBoard(board, n);
}

void printAvailableMoves(char board[][26], int n, char color) {
    printf("Available moves for %c:\n", color);
    
    // iterate through all positions
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (checkValidMove(board, n, color, row, col)) {
                printf("%c%c\n", 'a' + row, 'a' + col);
            }
        }
    }
}

// helper function
bool checkLegalInDirection(const char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) {
    char opponent = (colour == BLACK) ? WHITE : BLACK;
    
    // next spot 
    row += deltaRow;
    col += deltaCol;
    
    // at least one opponent's piece must be found
    if (!positionInBounds(n, row, col) || board[row][col] != opponent) {
        return false;
    }
    
    // continue 
    while (true) {
        row += deltaRow;
        col += deltaCol;
        
        // boundary check
        if (!positionInBounds(n, row, col)) {
            return false;
        }
        
        // if own piece
        if (board[row][col] == colour) {
            return true;
        }
        
        // if empty
        if (board[row][col] == UNOCCUPIED) {
            return false;
        }
        
    }
}

// helper function for printAvailableMoves
bool checkValidMove(const char board[][26], int n, char color, int row, int col) {
    // the spot must be empty
    if (board[row][col] != UNOCCUPIED) {
        return false;
    }
    
    // No need to create non-const copy - use board directly!
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
        for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
            if (deltaRow == 0 && deltaCol == 0) {
                continue;
            }
            
            if (checkLegalInDirection(board, n, row, col, color, deltaRow, deltaCol)) {
                return true;
            }
        }
    }
    
    return false;
}

void doMove(char board[][26], int n, char color, int row, int col) {
    // Use our optimized function - NULL means we don't track flips
    applyMove(board, n, color, row, col, NULL);
}

// check if a piece is stable (cannot be flipped) - a key helper function
bool isStablePiece(const char board[][26], int n, int row, int col) {
    char color = board[row][col];
    if (color == UNOCCUPIED) return false;

    // fully enclosed row/column check
    bool closedRow = true, closedCol = true;
    for (int i = 0; i < n; i++) {
        if (board[row][i] != color) closedRow = false;
        if (board[i][col] != color) closedCol = false;
    }
    if (closedRow || closedCol) return true;
    
    // 1. corners are always stable
    if ((row == 0 || row == n-1) && (col == 0 || col == n-1))
        return true;
        
    // 2. stable edges - continuous line of same color extending from corner
    bool stableNorth = true, stableSouth = true;
    bool stableEast = true, stableWest = true;
    
    // check north
    if (row > 0) {
        int r = row - 1;
        while (r >= 0 && board[r][col] == color) r--;
        stableNorth = (r < 0);
    }
    
    // check south
    if (row < n-1) {
        int r = row + 1;
        while (r < n && board[r][col] == color) r++;
        stableSouth = (r >= n);
    }
    
    // check west
    if (col > 0) {
        int c = col - 1;
        while (c >= 0 && board[row][c] == color) c--;
        stableWest = (c < 0);
    }
    
    // check east
    if (col < n-1) {
        int c = col + 1;
        while (c < n && board[row][c] == color) c++;
        stableEast = (c >= n);
    }
    
    // if stable in vertical or horizontal direction, it's a stable piece
    if ((stableNorth && stableSouth) || (stableEast && stableWest))
        return true;
        
    return false;
}

// game mode recognition - force player to create certain patterns
enum BoardPattern {
    NO_PATTERN,
    CORNER_CONTROL,
    EDGE_CONTROL,
    MOBILITY_ADVANTAGE,
    PARITY_ADVANTAGE
};

// recognize current board pattern
enum BoardPattern identifyPattern(const char board[][26], int n, char turn) {
    char opponent = getOpponent(turn);
    int myCorners = 0, opponentCorners = 0;
    int myEdges = 0, opponentEdges = 0;
    int myMoves = 0, opponentMoves = 0;
    
    // count corner and edge control
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if ((r == 0 || r == n-1) && (c == 0 || c == n-1)) {
                // corners
                if (board[r][c] == turn) myCorners++;
                else if (board[r][c] == opponent) opponentCorners++;
            } 
            else if (r == 0 || r == n-1 || c == 0 || c == n-1) {
                // edges
                if (board[r][c] == turn) myEdges++;
                else if (board[r][c] == opponent) opponentEdges++;
            }
            
            // count mobility
            if (board[r][c] == UNOCCUPIED) {
                if (checkValidMove(board, n, turn, r, c)) myMoves++;
                if (checkValidMove(board, n, opponent, r, c)) opponentMoves++;
            }
        }
    }
    
    // priority: corners > mobility > parity > edges
    if (myCorners > opponentCorners) 
        return CORNER_CONTROL;
    else if (myMoves > opponentMoves + 3)
        return MOBILITY_ADVANTAGE;
    else {
        int emptyCount = 0;
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (board[r][c] == UNOCCUPIED) emptyCount++;
            }
        }
        
        if (emptyCount % 2 == (turn == BLACK ? 1 : 0))
            return PARITY_ADVANTAGE;
        else if (myEdges > opponentEdges)
            return EDGE_CONTROL;
    }
    
    return NO_PATTERN;
}

// enhanced evaluation function - adjust weights based on recognized board pattern
int evaluateBoard(const char board[][26], int n, char turn) {
    char opponent = getOpponent(turn);
    int score = 0;
    int myCount = 0, opponentCount = 0;
    int myStableCount = 0, opponentStableCount = 0;
    int cornerBonus = 500, edgeBonus = 50, mobilityBonus = 20, parityBonus = 10;
    
    // recognize board pattern and adjust weights
    enum BoardPattern pattern = identifyPattern(board, n, turn);
    switch(pattern) {
        case CORNER_CONTROL:
            cornerBonus *= 2;  // double corner weight
            break;
        case MOBILITY_ADVANTAGE:
            mobilityBonus *= 2; // double mobility weight
            break;
        case PARITY_ADVANTAGE:
            parityBonus *= 3;  // triple parity weight
            break;
        case EDGE_CONTROL:
            edgeBonus *= 2;    // double edge weight
            break;
        default:
            break;
    }
    
    // count pieces and stable pieces
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (board[r][c] == turn) {
                myCount++;
                if (isStablePiece(board, n, r, c)) {
                    myStableCount++;
                    score += 40; // increase stable piece weight
                }
            } else if (board[r][c] == opponent) {
                opponentCount++;
                if (isStablePiece(board, n, r, c)) {
                    opponentStableCount++;
                    score -= 40;
                }
            }
        }
    }
    
    // position scoring - using enhanced weights
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (board[r][c] == turn) {
                // corners
                if ((r == 0 || r == n-1) && (c == 0 || c == n-1)) {
                    score += cornerBonus;
                } 
                // edges
                else if (r == 0 || r == n-1 || c == 0 || c == n-1) {
                    score += edgeBonus;
                }
                // C positions - neighbors of corner neighbors
                else if ((r == 2 && c == 0) || (r == 0 && c == 2) ||
                        (r == 2 && c == n-1) || (r == 0 && c == n-3) ||
                        (r == n-1 && c == 2) || (r == n-3 && c == 0) ||
                        (r == n-3 && c == n-1) || (r == n-1 && c == n-3)) {
                    score += 15;
                }
                
                // X positions - diagonal neighbors of corners
                if ((r == 1 && c == 1) && board[0][0] == UNOCCUPIED) {
                    score -= 150; // increase penalty for dangerous positions
                }
                if ((r == 1 && c == n-2) && board[0][n-1] == UNOCCUPIED) {
                    score -= 150;
                }
                if ((r == n-2 && c == 1) && board[n-1][0] == UNOCCUPIED) {
                    score -= 150;
                }
                if ((r == n-2 && c == n-2) && board[n-1][n-1] == UNOCCUPIED) {
                    score -= 150;
                }
                
            } else if (board[r][c] == opponent) {
                // reverse scoring for opponent positions
                if ((r == 0 || r == n-1) && (c == 0 || c == n-1)) {
                    score -= cornerBonus;
                } else if (r == 0 || r == n-1 || c == 0 || c == n-1) {
                    score -= edgeBonus;
                } else if ((r == 2 && c == 0) || (r == 0 && c == 2) ||
                        (r == 2 && c == n-1) || (r == 0 && c == n-3) ||
                        (r == n-1 && c == 2) || (r == n-3 && c == 0) ||
                        (r == n-3 && c == n-1) || (r == n-1 && c == n-3)) {
                    score -= 15;
                }
                
                // opponent's dangerous positions... need to defend this
                if ((r == 1 && c == 1) && board[0][0] == UNOCCUPIED) {
                    score += 150;
                }
                if ((r == 1 && c == n-2) && board[0][n-1] == UNOCCUPIED) {
                    score += 150;
                }
                if ((r == n-2 && c == 1) && board[n-1][0] == UNOCCUPIED) {
                    score += 150;
                }
                if ((r == n-2 && c == n-2) && board[n-1][n-1] == UNOCCUPIED) {
                    score += 150;
                }
            }
        }
    }
    
    // calculate mobility
    int myMoves = 0, opponentMoves = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (board[r][c] == UNOCCUPIED) {
                if (checkValidMove(board, n, turn, r, c)) {
                    myMoves++;
                }
                if (checkValidMove(board, n, opponent, r, c)) {
                    opponentMoves++;
                }
            }
        }
    }
    
    // mobility difference score
    int mobilityScore = (myMoves - opponentMoves) * mobilityBonus;
    score += mobilityScore;
    
    // parity strategy
    int emptyCount = n*n - myCount - opponentCount;
    if (emptyCount % 2 == 1) {
        score += parityBonus;
    }
    
    // game phase strategy
    int totalPieces = myCount + opponentCount;
    double fillRate = (double)totalPieces / (n * n);
    
    if (fillRate > 0.85) {
        // endgame: piece count is decisive
        score += (myCount - opponentCount) * 100;
    } else if (fillRate > 0.7) {
        // late game: stable pieces and mobility
        score += (myStableCount - opponentStableCount) * 50;
        score += (int)(mobilityScore * 0.5); // explicit cast to int
    } else if (fillRate > 0.3) {
        // mid game: balanced development
        score += (myStableCount - opponentStableCount) * 30;
        score += (int)(mobilityScore * 1.5); // explicit cast to int
    } else {
        // early game: strategic positions and mobility
        score += mobilityScore * 2;
    }
    
    return score;
}

// correct function definition at the end
bool hasAnyValidMove(const char board[][26], int n, char color) {
    char nonConstBoard[26][26];
    copyBoard(board, nonConstBoard, n);
    
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (checkValidMove(nonConstBoard, n, color, r, c)) {
                return true;
            }
        }
    }
    return false;
}

// opponent color helper function
char getOpponent(char color) {
    return (color == BLACK) ? WHITE : BLACK;
}

// calculate number of opponent pieces that would be flipped by placing a piece at the specified position
int countFlips(const char board[][26], int n, char color, int row, int col) {
    if (board[row][col] != UNOCCUPIED) {
        return 0;  // position already occupied, cannot place piece
    }
    
    // No need to copy - direct calculation is more efficient
    int totalFlips = 0;
    char opponent = (color == BLACK) ? WHITE : BLACK;
    
    // check eight directions
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
        for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
            if (deltaRow == 0 && deltaCol == 0) {
                continue;  // skip center point
            }
            
            int flips = 0;
            int r = row + deltaRow;
            int c = col + deltaCol;
            
            // count number of opponent pieces that can be flipped in current direction
            while (positionInBounds(n, r, c) && board[r][c] == opponent) {
                flips++;
                r += deltaRow;
                c += deltaCol;
            }
            
            // if this direction forms a sandwich, add to count
            if (flips > 0 && positionInBounds(n, r, c) && board[r][c] == color) {
                totalFlips += flips;
            }
        }
    }
    
    return totalFlips;
}

// New function: Apply move and return flip positions
int applyMove(char board[][26], int n, char color, int row, int col, int flippedPositions[][2]) {
    // Place the piece
    board[row][col] = color;
    int totalFlips = 0;
    char opponent = (color == BLACK) ? WHITE : BLACK;
    
    // Check all 8 directions
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
        for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
            if (deltaRow == 0 && deltaCol == 0) continue;
            
            // If this direction has valid flips
            if (checkLegalInDirection(board, n, row, col, color, deltaRow, deltaCol)) {
                int r = row + deltaRow;
                int c = col + deltaCol;
                
                // Flip pieces and record positions
                while (board[r][c] == opponent) {
                    board[r][c] = color;
                    
                    // Record position in our tracker array
                    if (flippedPositions != NULL) {
                        flippedPositions[totalFlips][0] = r;
                        flippedPositions[totalFlips][1] = c;
                    }
                    
                    totalFlips++;
                    r += deltaRow;
                    c += deltaCol;
                }
            }
        }
    }
    
    return totalFlips;
}

// New function: Undo a move
void undoMove(char board[][26], int n, char color, int row, int col, int flippedPositions[][2], int flipCount) {
    // Clear the original move
    board[row][col] = UNOCCUPIED;
    
    // Flip back all changed pieces
    char opponent = (color == BLACK) ? WHITE : BLACK;
    for (int i = 0; i < flipCount; i++) {
        int r = flippedPositions[i][0];
        int c = flippedPositions[i][1];
        board[r][c] = opponent;
    }
}
