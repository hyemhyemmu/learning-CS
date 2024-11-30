#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define ROW 3
#define COL 3

//初始化棋盘
void InitBoard(char board[ROW][COL], int row, int col);

//打印棋盘
void DisplayBoard(char board[ROW][COL], int row, int col);

//玩家下棋
void PlayerMove(char board[ROW][COL], int row, int col);

//电脑下棋
//找空白的地方随机下棋
void CompMove(char board[ROW][COL], int row, int col);

//判断输赢
/*
玩家 - "*"
电脑 - "#"
平局 - "Q"
继续 - "C"
*/
char IsWin(char board[ROW][COL], int row, int col);