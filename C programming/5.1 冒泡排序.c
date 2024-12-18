#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void bubble_sort(int arr[],int sz)
{
	//逐一向右引用
	int j = 0;
	for (j = 0; j < sz - 1; j++)
	{
		int k = 0;
		for (k=0;k<sz-1-j;k++) //一趟冒泡排序会把最大的数带到最后一位，所以之后每一次排序可以忽略最后面的数
			if (arr[k] > arr[k + 1]) //左右两个比较大小，把大的换到后面去
			{
				int temp = arr[k + 1];
				arr[k + 1] = arr[k];
				arr[k] = temp;
			}
	}


}




int main()
{
	int arr[] = { 0,3,4,2,1,5,6,9,7,8 };
	//目标是输出 0 1 2 3 4  5 6  7 8 9
	int i = 0;
	int sz = sizeof(arr) / sizeof(arr[0]);  //sz不能在函数中计算，因为传入arr[]传入的只是第一个数字的地址
	bubble_sort(arr, sz);
	for (i = 0; i < sz; i++)
	{
		printf("%d ",arr[i]);
	}


	return 0;
}