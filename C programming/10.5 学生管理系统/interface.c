#define _CRT_SECURE_NO_WARNINGS
#include "system.h"

enum Options
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	SHOW
};


void menu()
{
	printf("******************************\n");
	printf("******1. add      2. del******\n");
	printf("******3. search***************\n");
	printf("******0. exit           ******\n");
	printf("******************************\n");

}


int main()
{
	//导入系统
	System sys;
	//初始化系统
	if (Init(&sys))
	{
		printf("初始化失败！开辟内存失败！");
		return 1;
	}

	int input = 0;
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			AddStu(&sys);
			break;
		case DEL:
			DelStu(&sys);
			break;
		case SEARCH:
			SearchStu(&sys);
			break;
		case EXIT:
			Exit(&sys);
			printf("退出系统");
			break;
		default:
			printf("选择错误");
			break;

		}

	} while (input!=EXIT);
	return 0;
}