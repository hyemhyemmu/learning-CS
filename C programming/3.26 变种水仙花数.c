#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

/*
变种水仙花数 - Lily Number : 把任意的数字, 从中间拆分成两个数字, 比如1461可
以拆分成(1和461), (14和61), (146和1), 如果所有拆分后的乘积之和等于自身,
则是一个Lily Number。
例如 :
655 = 6 * 55 + 65 * 5
1461 = 1 * 461 + 14 * 61 + 146 * 1
求出5位数中的所有Lily Number。
*/

int islily(int i)
{
	//判断
	int j = 0;
	int arr[4] = { 0 };

	for (j = 1; j <= 4; j++)
	{
		int power = (int)pow(10, j);
		arr[j - 1] = (i / power) * (i % power);
	}

	int sum = 0;
	for (j = 0; j <= 3; j++)
	{
		sum += arr[j];
	}

	return sum == i;

}



int main()
{
	char ch = 0;
	int i = 0;
	for (i = 10000; i < 100000; i++)
	{
		if (islily(i))
		{
			printf("%d ", i);
		}
	}
	return 0;
}