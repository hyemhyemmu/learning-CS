#define _CRT_SECURE_NO_WARNINGS
#include "contact.h"

void menu()
{
	printf("******************************\n");
	printf("******1. add      2. del******\n");
	printf("******3. search   4. modify***\n");
	printf("******5. show     6. sort*****\n");
	printf("******0. exit           ******\n");
	printf("******************************\n");
	
}


int main()
{
	Contact con; //导入通讯录
	InitContact(&con); //初始化通讯录

	int input = 0;
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			AddContact(&con);
			break;
		case 2:
			DelContact(&con);
			break;
		case 3:
			SearchContact(&con);
			break;
		case 4:
			ModifyContact(&con);
			break;
		case 5:
			ShowContact(&con);
			break;
		case 6:
			SortContact(&con);
			break;
		case 0:
			printf("退出通讯录");
			break;
		default:
			printf("选择错误");
			break;

		}

	} while (input);
	return 0;
}