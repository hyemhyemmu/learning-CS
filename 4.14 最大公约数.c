#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//辗转相除法求最大公约数

int main()
{
	int m = 0, n = 0;
	printf("enter your two numbers:>");
	while (scanf("%d %d", &m, &n) != 2 || m == 0 || n == 0)
	{
		printf("invalid input! >");
		while (getchar() != '\n');
	}

	while (m % n!=0)
	{
		int temp = m % n;
		m = n;
		n = temp;
	}
	printf("%d",n);




	return 0;
}