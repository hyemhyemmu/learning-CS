#include <stdio.h>
#include <stdbool.h>
#define UNOCCUPIED 'U'
#define BLACK 'B'
#define WHITE 'W'

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
            printf("Enter move for color %c (RowCol): ", humanColor);
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
