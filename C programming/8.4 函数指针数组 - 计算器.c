#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void menu()
{
	printf("**************************\n");
	printf("****1. add     2. sub*****\n");
	printf("****3. mul     4. div*****\n");
	printf("****0. exit   ************\n");
}

int Add(int x, int y)
{
	return x + y;
}

int Sub(int a, int b) {
	return a - b; 
}

int Mul(int a, int b) {
	return a * b; 
}

int Div(int a, int b) {
	return a / b; 
}

int main()
{
	int input = 0;
	int x = 0;
	int y = 0;
	int ret = 0;
	int(*pfarr[])(int, int) = { 0,Add,Sub,Mul,Div };
	do
	{
		menu();
		printf("请选择>");
		scanf("%d", &input);

		if (input == 0)
		{
			printf("退出计算器。\n");
		}
		else if (input>=1 && input<=4)
		{
			printf("请输入两个操作数:>");
			scanf("%d %d", &x, &y);

			ret = pfarr[input](x, y);
			printf("%d\n", ret);
		}
		else
		{
			printf("错误输入\n");
		}

	} while (input);
	return 0;
}