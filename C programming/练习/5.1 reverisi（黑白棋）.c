#include <stdio.h>
#include <stdbool.h>
#define UNOCCUPIED 'U'
#define BLACK 'B'
#define WHITE 'W'
const double OCCUPIED_FACTOR = 0.7; // define "close to the end" as 0.7/1 the board being occupied
/**
 * for this smarter version, I tried to implement it with the classic "Minimax" algorithm,
 * with "Alpha-Beta Pruning" to improve the performance.
 */

// function prototype - explained when defined rather than here
bool checkLegalInDirection(char board[][26], int n, char color, int row, int col, int deltaRow, int deltaCol);
bool checkValidMove(char board[][26], int n, char color, int row, int col);
void boardConfigurations(char board[][26], int n);
void InitializeBoard(char board[][26], int n);
void printBoard(char board[][26], int n);
void printAvailableMoves(char board[][26], int n, char color);
void makeMove(char board[][26], int n, char color, int row, int col);
int countFlips(char board[][26], int n, char color, int row, int col);
bool hasValidMove(char board[][26], int n, char color);
void getComputerMove(char board[][26], int n, char computerColor, int *row, int *col);
void playGame(char board[][26], int n, char computerColor);
char getWinner(char board[][26], int n);
int findBestMove(const char board[][26], int n, char turn, int *row, int *col);
int minimax(char board[][26], int n, char turn, int depth, int alpha, int beta, bool isMaximizing);
int evaluateBoard(char board[][26], int n, char turn);
void copyBoard(const char source[][26], char dest[][26], int n);
bool hasAnyValidMove(char board[][26], int n, char color);
char getOpponent(char color);


// minimax search depth
#define MAX_DEPTH 4

// weight matrix -> 8*8 since the staff programs are based on 8*8 board
int positionWeights[8][8] = {
    {100, -20, 10, 5, 5, 10, -20, 100},
    {-20, -50, -2, -2, -2, -2, -50, -20},
    {10, -2, 8, 1, 1, 8, -2, 10},
    {5, -2, 1, 1, 1, 1, -2, 5},
    {5, -2, 1, 1, 1, 1, -2, 5},
    {10, -2, 8, 1, 1, 8, -2, 10},
    {-20, -50, -2, -2, -2, -2, -50, -20},
    {100, -20, 10, 5, 5, 10, -20, 100}
};

// // main function
// int main(){
//     int dimension;
//     printf("Enter the board dimension: ");
//     scanf("%d", &dimension);
//     char board[26][26];
//     char computerColor;
    
//     printf("Computer plays (B/W) : ");
//     scanf(" %c", &computerColor);
    
//     InitializeBoard(board, dimension);
//     printBoard(board, dimension);
    
//     // main game logic
//     playGame(board, dimension, computerColor);
    
//     return 0;
// }

// [MAIN GAME]
void playGame(char board[][26], int n, char computerColor) {
    char humanColor = (computerColor == BLACK) ? WHITE : BLACK;
    char currentPlayer = BLACK; // the example case says black always goes first
    bool gameOver = false;
    
    while (!gameOver) {
        // check if current player still able to move
        if (!hasValidMove(board, n, currentPlayer)) {
            // check if the other player still able to move
            char opponent = (currentPlayer == BLACK) ? WHITE : BLACK;
            if (!hasValidMove(board, n, opponent)) {
                // if both players cannot move, game over
                char winner = getWinner(board, n);
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
        
        // human plaer's round logic
        if (currentPlayer == humanColor) {
            char row, col;
            printf("Enter move for colour %c (RowCol): ", humanColor);
            scanf(" %c%c", &row, &col);
            
            int rowIdx = row - 'a';
            int colIdx = col - 'a';
            
            if (rowIdx < 0 || rowIdx >= n || colIdx < 0 || colIdx >= n || 
                !checkValidMove(board, n, humanColor, rowIdx, colIdx)) {
                printf("Invalid move.\n"); // game over staright away when invalid move!
                char winner = computerColor;
                printf("%c player wins.\n", winner);
                gameOver = true;
                continue;
            }
            
            makeMove(board, n, humanColor, rowIdx, colIdx);
            printBoard(board, n);
        } 

        // conputer round logic
        else {
            int computerRow, computerCol;
            getComputerMove(board, n, computerColor, &computerRow, &computerCol);
            printf("Computer places %c at %c%c.\n", computerColor, 
                   'a' + computerRow, 'a' + computerCol);
            
            makeMove(board, n, computerColor, computerRow, computerCol);
            printBoard(board, n);
        }
        
        // switch turn
        currentPlayer = (currentPlayer == BLACK) ? WHITE : BLACK;
    }
}

// computer move logic 
void getComputerMove(char board[][26], int n, char computerColor, int *row, int *col) {
    int maxScore = -1;
    *row = -1;
    *col = -1;
    
    // iterate all the board to find the best spot
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (checkValidMove(board, n, computerColor, r, c)) {
                int score = countFlips(board, n, computerColor, r, c);
                
                // update the heightest score (when same, keep the smaller index one)
                if (score > maxScore || 
                   (score == maxScore && r < *row) || 
                   (score == maxScore && r == *row && c < *col)) {
                    maxScore = score;
                    *row = r;
                    *col = c;
                }
            }
        }
    }
}

// helper function for getComputerMove, to calculate the score of a move
int countFlips(char board[][26], int n, char color, int row, int col) {
    char opponent = (color == BLACK) ? WHITE : BLACK;
    int totalFlips = 0;
    
    // check 8 directions, pretty much same as checkValidMove
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
        for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
            if (deltaRow == 0 && deltaCol == 0) {
                continue;
            }
            
            int flips = 0;
            int r = row + deltaRow;
            int c = col + deltaCol;
            
            // count flipperble pieces
            while (r >= 0 && r < n && c >= 0 && c < n && board[r][c] == opponent) {
                flips++;
                r += deltaRow;
                c += deltaCol;
            }
            
            // confirm the end is own piece
            if (r >= 0 && r < n && c >= 0 && c < n && board[r][c] == color) {
                totalFlips += flips;
            }
        }
    }
    
    return totalFlips;
}

// check if a player has valid move
bool hasValidMove(char board[][26], int n, char color) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (checkValidMove(board, n, color, row, col)) {
                return true;
            }
        }
    }
    return false;
}

// get the winner
char getWinner(char board[][26], int n) {
    int blackCount = 0, whiteCount = 0;
    
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            if (board[row][col] == BLACK) {
                blackCount++;
            } else if (board[row][col] == WHITE) {
                whiteCount++;
            }
        }
    }
    
    if (blackCount > whiteCount) {
        return BLACK;
    } else if (whiteCount > blackCount) {
        return WHITE;
    } else {
        return UNOCCUPIED; 
    }
}

// functions
void InitializeBoard(char board[][26], int n) {
    for(int row = 0; row < n; row++) {      
        for(int col = 0; col < n; col++) {  
            board[row][col] = UNOCCUPIED;
        }
    }
    
    // set initial 4 pieces
    int center = n / 2;
    board[center-1][center-1] = WHITE;
    board[center-1][center] = BLACK;
    board[center][center-1] = BLACK;
    board[center][center] = WHITE;
}

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

// helper function fro checkValidMove, given specific direction
bool checkLegalInDirection(char board[][26], int n, char color, int row, int col, int deltaRow, int deltaCol) {
    char opponent = (color == BLACK) ? WHITE : BLACK;
    
    // next spot 
    row += deltaRow;
    col += deltaCol;
    
    // at least one opponent's piece must be found
    if (row < 0 || row >= n || col < 0 || col >= n || board[row][col] != opponent) {
        return false;
    }
    
    // continue 
    while (true) {
        row += deltaRow;
        col += deltaCol;
        
        // boundary check
        if (row < 0 || row >= n || col < 0 || col >= n) {
            return false;
        }
        
        // if own piece
        if (board[row][col] == color) {
            return true;
        }
        
        // if empty
        if (board[row][col] == UNOCCUPIED) {
            return false;
        }
        
    }
}

// helper function for printAvailableMoves
bool checkValidMove(char board[][26], int n, char color, int row, int col) {
    // the spot must be empty
    if (board[row][col] != UNOCCUPIED) {
        return false;
    }
    
    // check 8 directions: (-1,0), (1,0), (0,-1), (0,1), (-1,-1), (-1,1), (1,-1), (1,1)
    // can be done using two loops
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
        for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
            if (deltaRow == 0 && deltaCol == 0) {
                continue;
            }
            
            // if any is valid, then the spot is valid as well
            if (checkLegalInDirection(board, n, color, row, col, deltaRow, deltaCol)) {
                return true;
            }
        }
    }
    
    return false;
}

// move!
void makeMove(char board[][26], int n, char color, int row, int col) {
    // place the piece
    board[row][col] = color;
    
    for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
        for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
            if (deltaRow == 0 && deltaCol == 0) {
                continue;
            }
            
            // if can flip this direction
            if (checkLegalInDirection(board, n, color, row, col, deltaRow, deltaCol)) {
                int r = row + deltaRow;
                int c = col + deltaCol;
                char opponent = (color == BLACK) ? WHITE : BLACK;
                
                // flip all the pieces
                while (board[r][c] == opponent) {
                    board[r][c] = color;
                    r += deltaRow;
                    c += deltaCol;
                }
            }
        }
    }
}

// find the best move for computer
int findBestMove(const char board[][26], int n, char turn, int *row, int *col) {
    // make a copy for search 

    // i know this may not be the best way since it costs memory,
    // but i can't think of a better way at the moment...
    // will figure out later

    char boardCopy[26][26];
    copyBoard(board, boardCopy, n);
    
    int bestScore = -99999;
    *row = -1;
    *col = -1;
    
    // make a greedy move first
    int maxFlips = -1;
    int greedyRow = -1;
    int greedyCol = -1;
    
    // iterate all the pos
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (checkValidMove(boardCopy, n, turn, r, c)) {
                // backup plan using greddy algo.
                int flips = countFlips(boardCopy, n, turn, r, c);
                if (flips > maxFlips) {
                    maxFlips = flips;
                    greedyRow = r;
                    greedyCol = c;
                }
                
                // move
                char tempBoard[26][26];
                copyBoard(boardCopy, tempBoard, n);
                makeMove(tempBoard, n, turn, r, c);
                
                // evaluate the plan using minimax
                int score = minimax(tempBoard, n, getOpponent(turn), MAX_DEPTH - 1, -99999, 99999, false);
                
                // update the best move
                if (score > bestScore) {
                    bestScore = score;
                    *row = r;
                    *col = c;
                }
            }
        }
    }
    
    // use the backplan (greedy) if no better move found
    if (*row == -1 && *col == -1) {
        *row = greedyRow;
        *col = greedyCol;
    }
    
    return bestScore;
}

// minimax algo. using Alpha-Beta Pruning
int minimax(char board[][26], int n, char turn, int depth, int alpha, int beta, bool isMaximizing) {
    char opponent = getOpponent(turn);
    
    // base case: max depth or no more move 
    if (depth == 0 || (!hasAnyValidMove(board, n, turn) && !hasAnyValidMove(board, n, opponent))) {
        return evaluateBoard(board, n, isMaximizing ? turn : opponent);
    }
    
    // have to let opponent move if we don't...
    if (!hasAnyValidMove(board, n, turn)) {
        return minimax(board, n, opponent, depth - 1, alpha, beta, !isMaximizing);
    }
    
    if (isMaximizing) {
        int maxEval = -999; // just a random negative num, make it BIG
        
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (checkValidMove(board, n, turn, r, c)) {
                    char tempBoard[26][26];
                    copyBoard(board, tempBoard, n);
                    makeMove(tempBoard, n, turn, r, c);
                    
                    int eval = minimax(tempBoard, n, opponent, depth - 1, alpha, beta, false);
                    maxEval = (eval > maxEval) ? eval : maxEval;
                    alpha = (alpha > eval) ? alpha : eval;
                    
                    if (beta <= alpha)
                        break;
                }
            }
            
            if (beta <= alpha)
                break;
        }
        
        return maxEval;
    } else {
        int minEval = 999;
        
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (checkValidMove(board, n, turn, r, c)) {
                    char tempBoard[26][26];
                    copyBoard(board, tempBoard, n);
                    makeMove(tempBoard, n, turn, r, c);
                    
                    int eval = minimax(tempBoard, n, opponent, depth - 1, alpha, beta, true);
                    minEval = (eval < minEval) ? eval : minEval;
                    beta = (beta < eval) ? beta : eval;
                    
                    if (beta <= alpha)
                        break;
                }
            }
            
            if (beta <= alpha)
                break;
        }
        
        return minEval;
    }
}

// evaluate the board
int evaluateBoard(char board[][26], int n, char turn) {
    char opponent = getOpponent(turn);
    int score = 0;
    int myCount = 0, opponentCount = 0;
    int myMoves = 0, opponentMoves = 0;
    
    // score the weight
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (board[r][c] == turn) {
                myCount++;
                // using the matrix
                if (n == 8) {
                    score += positionWeights[r][c];
                } else {
                    // in case it is other size
                    if ((r == 0 || r == n-1) && (c == 0 || c == n-1)) {
                        score += 100; 
                    } else if (r == 0 || r == n-1 || c == 0 || c == n-1) {
                        score += 5; 
                    }
                }
            } else if (board[r][c] == opponent) {
                opponentCount++;
                // minus opponent's weight
                // same logic as previous one, just flip the sign
                if (n == 8) {
                    score -= positionWeights[r][c];
                } else {
                    if ((r == 0 || r == n-1) && (c == 0 || c == n-1)) {
                        score -= 100; 
                    } else if (r == 0 || r == n-1 || c == 0 || c == n-1) {
                        score -= 5; 
                    }
                }
            }
            
            // compare movable pieces 
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
    
    // factor
    score += (myMoves - opponentMoves) * 10;
    
    // we should take more care with the number of pieces when close to the end
    int totalPieces = myCount + opponentCount;
    int maxPieces = n * n;
    if (totalPieces > maxPieces * OCCUPIED_FACTOR) { // the factor can be redefined though
        score += (myCount - opponentCount) * 30;
    }
    
    return score;
}

// helper: copy the board
void copyBoard(const char source[][26], char dest[][26], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dest[i][j] = source[i][j];
        }
    }
}

// helper: check if has any valid move for the color holder
bool hasAnyValidMove(char board[][26], int n, char color) {
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (checkValidMove(board, n, color, r, c)) {
                return true;
            }
        }
    }
    return false;
}

// helper
char getOpponent(char color) {
    return (color == BLACK) ? WHITE : BLACK;
}
