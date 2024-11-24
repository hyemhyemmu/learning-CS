#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
一只青蛙跳台阶，每次可以跳 1 级或 2 级台阶。
假设台阶总共有 n 级，问青蛙有多少种不同的跳法，可以跳上第 n 级台阶？
*/


//f(n)=f(n-1)+f(n-2)

int method(int n)
{
	if (n == 1)
	{
		return 1;
	}
	else if (n == 2)
	{
		return 2;
	}
	else
		return method(n - 1) + method(n - 2);
	
}



int main()
{
	int n = 0;
	int output = 0;
	printf("Which floor do u want to go? >");
	while (scanf("%d", &n) != 1||n<=0)
	{
		printf("invalid input!");
		while (getchar() != '\n');
	} //ensure valid input

	output = method(n);
	printf("\nnumber of method to go to %d floor is %d!", n, output);

	return 0;
}