#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
创建一个整形数组, 完成对数组的操作
实现函数init()初始化数组为全0
实现print()打印数组的每个元素
reverse()函数完成数组元素的逆置。
*/


void print(int arr[], int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}


void reverse(int arr[], int sz)
{
	int left = 0;
	int right = sz - 1;
	int i = 0;
	int temp = 0;
	while (left < right)
	{
		temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
		left++;
		right--;
	}
}

void init(int arr[], int sz)
{
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		arr[i] = 0;
	}
}


int main()
{
	int arr[10] = { 0,1,2,3,4,5,6,7,8,9 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	print(arr,10);
	reverse(arr,10);
	print(arr,10);
	init(arr, 10);
	print(arr, 10);

	return 0;
}