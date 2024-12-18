#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

//输出1-100的质数

int is_prime(int i)
{
	int j = 0;
	for (j = 2; j < i - 1; j++)
	{
		if (i % j == 0)
			return 0;
	}
	return 1;  //return 1 when i is a prime num
}



int main()
{
	int i = 0;
	int count = 0;
	for (i = 2; i <= 100; i++)
	{
		if (is_prime(i)) //如果返回值为1，就执行，反之不执行。
		{
			count++;
			printf("%d ", i);
		}
	}
	printf("\nThere are %d numbers.", count);

	return 0;
}