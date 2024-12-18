#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//接收一个整型值，按照顺序打印每一位

/*
递归过程：
print(1234)
print(123) 4
print(12) 3 4
print(1) 2 3 4
1 2 3 4 
*/

void print(int num)
{
	if (num > 9)
	{
		print(num / 10); //刨除个位，递归前面位数
	}
	printf("%d ",num % 10); //输出个位
}




int main()
{
	int num = 0;
	printf("Please enter number you want to output:> ");
	scanf("%d", &num);
	while (getchar() != '\n');

	print(num);

	return 0;
}