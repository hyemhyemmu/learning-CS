#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//计算1/1-1/2+......+1/100的和
//偶数项为-1

int main()
{
	int flag = 1;
	int i = 0;
	double sum = 0; //有小数，不能再用整型
	for (i = 1; i <= 100; i++)
	{
		 sum = sum + flag*(1.0 / i);
		 flag = -flag;
	}
	printf("%lf", sum);

	return 0;
}