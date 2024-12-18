#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//函数递归实现计算斐波那契数列

/*
fib(n)=1,n<=2
fib(n)=fib(n-1)+fib(n-2),n>2
*/

int fib(int n)
{
	if (n <= 2)
		return 1;
	else
		return fib(n - 1) + fib(n - 2);
}




int main()
{
	int n = 0;
	printf("你想要第几位的斐波那契数？> ");
	while (scanf("%d", &n) != 1 || n <= 0)
	{
		printf("\n错误输入！请重试：>");
		while (getchar() != '\n');
	}

	printf("整个斐波那契数列为: ");
	for (int i = 1; i <= n; i++)
	{
		printf("%d ",fib(i));
	}

	int output = fib(n);
	printf("\n第%d个的斐波那契数为%d", n, fib(n));


	return 0;
}