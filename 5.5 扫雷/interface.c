#define _CRT_SECURE_NO_WARNINGS
#include "game.h"


void game()
{
	char mine[ROWS][COLS] = { 0 };   //存放埋好的雷的信息
	char show[ROWS][COLS] = { 0 };   //存放排查信息
	InitBoard(mine, ROWS, COLS,'0');
	InitBoard(show, ROWS, COLS,'*');

	//设置雷
	SetMine(mine, ROW, COL);
	DisplayBoard(show, ROW, COL); //打印棋盘

	//排查雷
	FindMine(mine, show, ROW, COL);
}




void menu()
{
	printf("*************************\n");
	printf("****1. play 0. exit******\n");
	printf("*************************\n");
}


int main()
{
	int srand = ((unsigned)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("请选择：>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出");
			break;
		default:
			printf("选择错误");
			break;
		}
	} while (input);


	return 0;
}