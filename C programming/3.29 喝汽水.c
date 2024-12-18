#define _CRT_SECURE_NO_WARNINGS

//喝汽水，1瓶汽水1元，2个空瓶可以换一瓶汽水，输入钱数，求能喝多少瓶汽水？

#include <stdio.h>

int main()
{
	int money = 0;
	printf("what is your money? :>");
	scanf("%d", &money);

	int total = money;
	int empty = money;

	while (empty / 2 != 0)
	{
		total += empty / 2;
		empty = empty / 2 + empty % 2;
	}

	printf("Total coke you can drink is %d!", total);

	return 0;
}