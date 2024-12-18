#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void menu()
{
	printf("*****************************\n");
	printf("*****  1. play 0. exit  *****\n");
	printf("*****************************\n");
}


void game() //游戏的主程序
{
	//首先要初始化棋盘
	char board[ROW][COL] = { 0 };
	InitBoard(board, ROW, COL); //我们希望把棋盘大小也一起传入，但是这里就默认为3

	//打印棋盘
	DisplayBoard(board, ROW, COL);
	
	char ret = 0;
	//下棋
	while (1)
	{
		//玩家先走
		PlayerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		//判断输赢
		ret = IsWin(board, ROW, COL);
		if (ret != 'C') //只要不是继续就全部退出
			break;
		//电脑继续走
		CompMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		//判断输赢
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;
	}
	if (ret == '*')
	{
		printf("玩家赢了！\n");
	}
	else if (ret == '#')
	{
		printf("电脑赢了！\n");
	}
	else if (ret == 'Q')
	{
		printf("平局~\n");
	}
}




int main()
{
	int input = 0;
	srand((unsigned int)time(NULL)); //设置随机数起点
	do
	{
		menu(); //打印菜单
		printf("请选择：> ");
		scanf("%d", &input); //获取输入
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("输入错误\n");
			break;
		}
	} while (input != 0); //菜单至少出现一次




	return 0;
}