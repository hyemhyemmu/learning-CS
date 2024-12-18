#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//求某个数字在内存中的二进制中的1的个数


int main()
{
	int n = 0;
	printf("输入一个数:> ");
	while (scanf("%d", &n) != 1)
	{
		printf("invalid input!\n");
		while (getchar() != '\n');
	}

	int count = 0;
	while (n != 0)
	{
		if ((n & 1) == 1)
		{
			count++;
		}
		n=n >> 1; //计数完后就抛弃最右位
	}
	printf("%d的二进制内存地址中有%d个1！", n, count);

	return 0;
}