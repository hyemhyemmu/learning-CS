#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define ROW 9
#define COL 9
#define ROWS ROW+2
#define COLS COL+2

//雷的个数
#define EASY_COUNT 10

//初始化棋盘
void InitBoard(char board[ROWS][COLS], int rows, int cols,char set);
//展示棋盘
void DisplayBoard(char board[ROWS][COLS], int row, int col); 
//布置地雷
void SetMine(char board[ROWS][COLS], int row, int col);

//功能：展开一片（通过递归实现）
void Expand(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y);
//排查地雷 （细节：FindMine函数调用了Expand函数,所以必须把Expand放在前面）
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);