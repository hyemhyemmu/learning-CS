#include <stdio.h>
#include <stdbool.h>
#define UNOCCUPIED 'U'
#define BLACK 'B'
#define WHITE 'W'

// function prototype
bool checkLegalInDirection(char board[][26], int n, char color, int row, int col, int deltaRow, int deltaCol);
bool checkValidMove(char board[][26], int n, char color, int row, int col);
void boardConfigurations(char board[][26], int n);
void InitializeBoard(char board[][26], int n);
void printBoard(char board[][26], int n);
void printAvailableMoves(char board[][26], int n, char color);
void makeMove(char board[][26], int n, char color, int row, int col);

// main function
int main(){
    int dimension;
    printf("Enter the board dimension: ");
    scanf("%d", &dimension);
    char board[26][26]; // 使用固定大小的数组，避免边界问题

    InitializeBoard(board, dimension);
    printBoard(board, dimension);

    // configuration
    boardConfigurations(board, dimension);

    // print available moves
    printAvailableMoves(board, dimension, 'W');
    printAvailableMoves(board, dimension, 'B');

    // move 
    printf("Enter a move:\n");
    char color, row, col;
    scanf(" %c%c%c", &color, &row, &col);
    int rowIdx = row - 'a';
    int colIdx = col - 'a';
    bool isValidMove = checkValidMove(board, dimension, color, rowIdx, colIdx);
    if (isValidMove){
        printf("Valid move.\n");
        makeMove(board, dimension, color, rowIdx, colIdx);
    } else {
        printf("Invalid move.\n");
    }

    // print the board
    printBoard(board, dimension);
    return 0;
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
