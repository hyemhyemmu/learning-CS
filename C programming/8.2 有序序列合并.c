#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
输入包含三行,

第一行包含两个正整数n,m,用空格分隔。n表示第二行第一个升序序列中数字的个
数,m表示第三行第二个升序序列中数字的个数。

第二行包含n个整数,用空格分隔。

第三行包含m个整数,用空格分隔。

输出描述:
输出为一行,输出长度为n+m的升序序列,即长度为n的升序序列和长度为m的升序
序列中的元素重新进行升序序列排列合并。
*/

int main()
{
	int n = 0;
	int m = 0;
	scanf("%d %d", &n, &m);

	int arr_1[1000];
	int arr_2[1000];
	int arr_3[2000];


	int i = 0;
	for (i = 0; i < n; i++)
	{
		scanf("%d", arr_1 + i);
	}

	for (i = 0; i < m; i++)
	{
		scanf("%d", arr_2 + i);
	}

	int j = 0;
	int k = 0;
	int r = 0;

	while (j < n && k < m)
	{
		if (arr_1[i] > arr_2[j])
		{
			arr_3[r++] = arr_1[i];
			j++;
		}
		else
		{
			arr_3[r++] = arr_2[k];
			i++;
		}
	}

	if (j < n)
	{
		for (; j < n; j++)
		{
			arr_3[r++] = arr_1[j];
		}
	}
	else
	{
		for (; k < m; k++)
		{
			arr_3[r++] = arr_2[k];
		}
	}
	return 0;
}