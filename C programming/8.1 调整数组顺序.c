#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//输入一个10位数的数组，实现一个函数使得所有的奇数在数组的前半部分，
//所有偶数在数组的后半部分

void move_odd_even(int* arr, int sz)
{
	int left = 0;
	int right = sz - 1;

	//坑！如果是纯奇数/偶数数组，很有可能发生数组越界
	while (left<right)
	{
		//偶数
		while (left < right && arr[left] % 2 == 1)
		{
			left++;
		}

		//奇数
		while (left < right && arr[right] % 2 == 0)
		{
			right--;
		}

		//交换
		if (left < right)
		{
			int temp = arr[left];
			arr[left] = arr[right];
			arr[right] = temp;

			left++;
			right--;
		}
	}
		
}


int main()
{
	//输入
	int arr[10] = { 0 };
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		scanf("%d", arr + i);
	}
	//调整
	int sz = sizeof(arr) / sizeof(arr[0]);
	move_odd_even(&arr, sz);
	//输出
	for (i = 0; i < 10; i++)
	{
		printf("%d", arr[i]);
	}

	return 0;
}