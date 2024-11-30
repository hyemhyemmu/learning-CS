#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void InitBoard(char board[ROW][COL], int row, int col)
{
	//利用数组迭代打印一个空棋盘
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	for (i = 0; i < row; i++)
	{
		//打印数据
		int j = 0;
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			if (j < col - 1)
				printf("|"); //最后一项后面不再打印分隔符
		}
		printf("\n");
		  
		//打印分割行
		if (i < row - 1) //在这里就加判断是因为行数才是影响分隔符的因素
		{
			int j = 0;
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
					printf("|"); //最后一项后面不再打印分隔符
			}
			printf("\n");
		}
	}
}


void PlayerMove(char board[ROW][COL], int row, int col)
{
	printf("轮到玩家了！\n");
	int x = 0;
	int y = 0;
	while (1)
	{
		printf("请输入坐标:> ");
		if (scanf("%d %d", &x, &y) != 2)
		{
			printf("输入错误，请输入两个整数\n");
			while (getchar() != '\n'); // 清除输入缓冲区
			continue;
		}

		// 范围合法性判断后再下棋
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			// 判断格子是否被下了
			if (board[x - 1][y - 1] == ' ')
			{
				board[x - 1][y - 1] = '*'; // 下棋
				break;
			}
			else
			{
				printf("格子已经被下了！\n");
			}
		}
		else
		{
			printf("坐标非法，请重新输入\n");
		}
	}
}


void CompMove(char board[ROW][COL], int row, int col)
{
	printf("轮到电脑了！\n");
	int x = 0;
	int y = 0;

	

	while (1)
	{
		x = rand() % row; //0-2
		y = rand() % col; //0-2
		if (board[x][y] == ' ')
		{
			board[x][y] = '#'; 
			break;
		}
	}



}



//判断是否满了？ 满了返回1，不满返回0
int IsFull(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
				return 0;
		}
	}
	return 1;
}





char IsWin(char board[ROW][COL], int row, int col)
{
	//行
	int i = 0;
	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ')
		{
			return board[i][0]; //这里是一个很巧妙的设计，减少了判断
		}
	}
	//列
	int j = 0;
	for (j = 0; j < col; j++)
	{
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[1][j] != ' ')
		{
			return board[0][j]; 
		}
	}
	//对角线
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ') //左对角线
	{
		return board[0][0];
	}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ') //右对角线
	{
		return board[0][2];
	}

	//如果此时还没有输出，就判断是否平局
	//要先看是否放满了，因为判断输赢的操作是每一步下棋之后都会进行的
	if (IsFull(board, row, col)) 
	{
		return 'Q';
	}

	//不然游戏就继续
	return 'C';
}