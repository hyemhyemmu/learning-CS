#define _CRT_SECURE_NO_WARNINGS

//求出0-10000之间所有的“水仙花数”并输出
//“水仙花数”：一个n位数，各位数的n次方之和恰好等于本身

#include <stdio.h>
#include <math.h>

int power(int X, int Y)
{
	int i = 1;
	int sum = 1;
	for (i = 1; i <= Y; i++)
	{
		sum *= X;
	}
	return sum;
}

int is_num(int n)
{
	//判断位数
	int i = (n == 0) ? 1 : log10(n) + 1; //i存放的是位数

	 int temp = n;//副本
	//加和
	int sum = 0;
	int num = i; //循环次数等于位数
	int j = 0;
	

	for (j = 0; j < i; j++)
	{
		int digit = 0;
		digit = temp % 10;  //每次都取最后一位计算
		sum += power(digit, i);
		temp = temp / 10;   //丢弃最后一位
	}
	//验证是否为水仙花数
	if (n == sum)
	{
		return 1;
	}

	return 0;
}



int main()
{
	int n = 0;
	for (n = 0; n <= 10000; n++)
	{
		
		if (is_num(n))
		{
			printf("%d ", n);
		}
	}
	


	return 0;
}
