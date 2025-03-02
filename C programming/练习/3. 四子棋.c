#define ROWS 6
#define COLS 6
#define EMPTY '-'
#define RED 'R'
#define YELLOW 'Y'
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 

// function prototypes
char* initialBoard();
void printBoard(char gameBoard[][COLS]);
int getInput(char gameBoard[][COLS], int turn); 
void insertPiece(char gameBoard[][COLS], int columnEntered, int* turn);
bool checkOneDirection(char gameBoard[][COLS], int row, int col, int rowDir, int colDir);
bool checkWinner(char gameBoard[][COLS]);

// main function 
int main(){
    char (*gameBoard)[COLS] = (char (*)[COLS])initialBoard();
    if (gameBoard == NULL){
        printf("game initialization failed!");
        return 1;
    }
    
    int turn = 0;  
    bool gameOver = false;

    while(!gameOver){
        printBoard(gameBoard);
        
        if (turn % 2 == 0) {
            printf("Red, please enter a valid column number (0-5): ");
        } else {
            printf("Yellow, please enter a valid column number (0-5): ");
        }
        
        int column = getInput(gameBoard, turn);
        insertPiece(gameBoard, column, &turn);
        
        if (checkWinner(gameBoard)) {
            gameOver = true;
            if ((turn - 1) % 2 == 0) {
                printf("Red wins!\n");
            } else {
                printf("Yellow wins!\n");
            }
            printf("Final board: \n");
            printBoard(gameBoard);
            break;  // Exit the loop immediately
        } 
        else {
            bool boardFull = true;
            for (int col = 0; col < COLS; col++) {
                if (gameBoard[0][col] == EMPTY) {
                    boardFull = false;
                    break;
                }
            }
            
            if (boardFull) {
                gameOver = true;
                printf("It's a tie\n");  // Changed from "Tie game!"
                printf("Final board: \n");
                printBoard(gameBoard);
                break;
            }
        }
    }
    
    // Only print final board if game ends unexpectedly
    if (!gameOver) {
        printf("Final board: \n");
        printBoard(gameBoard);
    }
    
    free(gameBoard);
    return 0;
}

// functions 
char* initialBoard(){
    char *ptr = (char *)malloc(sizeof(char) * ROWS * COLS);
    if (ptr==NULL){
        printf("Memory allocation failed\n");
        return NULL;
    }
    else{
        for (int i = 0; i < ROWS * COLS; i++) {
            ptr[i] = EMPTY;
        }
        return ptr;
    }
}



void printBoard(char gameBoard[][COLS]){
    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLS; col++){
            printf("%c", gameBoard[row][col]);
        }
        printf("\n");
    }
}

// i choose to use number to represent turns rather than char cuz this will be fatser
int getInput(char gameBoard[][COLS], int turn) {
    int columnEntered;
    int validInput = 0;
    
    while (!validInput) {
        if (scanf("%d", &columnEntered) != 1) {
            while (getchar() != '\n');
            printf("%s, please enter a valid column number (0-5): ", 
                   (turn % 2 == 0) ? "Red" : "Yellow");
            continue;
        }
        
        if (columnEntered < 0 || columnEntered >= COLS || 
            gameBoard[0][columnEntered] != EMPTY) {
            printf("%s, please enter a valid column number (0-5): ", 
                   (turn % 2 == 0) ? "Red" : "Yellow");
            continue;
        }
        
        validInput = 1;
    }
    
    return columnEntered;
}


void insertPiece(char gameBoard[][COLS], int columnEntered, int* turn){
    char piece = (*turn % 2 == 0) ? RED : YELLOW;
    
    for (int row = ROWS - 1; row >= 0; row--) {
        if (gameBoard[row][columnEntered] == EMPTY) {
            gameBoard[row][columnEntered] = piece;
            (*turn)++;  // Increment turn after inserting piece
            break;
        }
    }
}


bool checkOneDirection(char gameBoard[][COLS], int row, int col, int rowDir, int colDir) {
    char piece = gameBoard[row][col];
    
    if (piece == EMPTY) {
        return false;
    }
    
    int count = 1;
    
    for (int i = 1; i <= 3; i++) {  
        int newRow = row + i * rowDir;
        int newCol = col + i * colDir;
        
        // boundary check
        if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS) {
            return false;  
        }
        
        if (gameBoard[newRow][newCol] != piece) {
            return false;  
        }
        
        count++;  
    }
    
    return (count == 4);
}    

bool checkWinner(char gameBoard[][COLS]){
    // define all the directions
    int directions[4][2] = {
        {0, 1},  
        {1, 0},  
        {1, 1},  
        {1, -1}  
    };
    
    for (int row = 0; row < ROWS; row++) {
        for (int col = 0; col < COLS; col++) {
            if (gameBoard[row][col] == EMPTY) {
                continue;
            }
            
            for (int dir = 0; dir < 4; dir++) {
                int rowDir = directions[dir][0];
                int colDir = directions[dir][1];
                
                if (checkOneDirection(gameBoard, row, col, rowDir, colDir)) {
                    return true;  
                }
            }
        }
    }
    
    return false;
}