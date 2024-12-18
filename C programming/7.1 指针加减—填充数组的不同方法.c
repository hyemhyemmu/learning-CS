#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

//填充数组的不同方法

int main()
{
	int arr[10] = { 0 };
	int i = 0;
	int sz = sizeof(arr) / sizeof(arr[0]);

	//数组的方法
	for (i = 0; i < sz; i++)
	{
		arr[i] = i;
		printf("%d ", arr[i]);
	}

	//指针的方法1
	int* p = arr; //&arr[0]
	for (i = 0; i < sz; i++)
	{
		*p++ = i; //*p=i; *p++
		printf("%d ", arr[i]);
	}

	//指针的方法2
	int* p = arr; //&arr[0]
	for (i = 0; i < sz; i++)
	{
		*(p+i) = i; //把[0]右侧的第i项赋值为i
		printf("%d ", arr[i]);
	}

	return 0;
}