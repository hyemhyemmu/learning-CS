#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//计算n的阶乘，使用函数递归与迭代

/*
frac(n)=n*frac（n-1)
*/


int frac(int n)
{

	if (n == 1)
		return 1; //基准情况
	else
		return n*frac(n-1);
}




int main()
{
	int n = 0;
	printf("Whose factorial do you want? > ");
	while (scanf("%d", &n) != 1 || n<=0)  //ensure valid input
	{
		printf("\nInvalid input, please try again! >");
		while (getchar() != '\n');
	}

	int output = frac(n);
	printf("\nThe result is %d ", output);

	return 0;
}