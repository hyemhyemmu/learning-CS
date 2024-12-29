#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//动态整数数组
//要求：编写一个程序，先让用户输入一个数字n，然后动态分配一个能存储n个整数的数组。
//接着让用户输入这n个数，存入数组后将其排序并打印出来。最后要正确释放内存。

//qsort比较函数的实现
int compare_int(const void* e1, const void* e2)
{
	return (*(int*)e1 - *(int*)e2);
}


int main()
{
	int n = 0;
	printf("请输入你的数组元素个数:>");
	if (scanf("%d", &n) != 1 || n <= 0)
	{
		printf("输入无效，请输入一个正整数。\n");
		return 1;
	}
	while (getchar() != '\n');

	int* arr = (int*)calloc(n, sizeof(int));

	if (arr == NULL)
	{
		printf("%s", strerror(errno));
	}

	int i = 0;
	printf("请输入你的数组元素:>");
	for (i = 0; i < n; i++)
	{
		if (scanf("%d", &arr[i]) != 1)
		{
			printf("输入无效，程序退出。\n");
			free(arr); //无效的时候也要释放内存
			return 1;
		}
		while (getchar() != '\n');
	}
	

	//排序
	qsort(arr, n, sizeof(int), compare_int);


	for (i = 0; i < n; i++)
	{
		printf("%d ", *(arr + i));
	}


	free(arr);
	arr = NULL;
	return 0;
}