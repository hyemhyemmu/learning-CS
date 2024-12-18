#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
请编写一个 C 语言程序，实现以下功能：

接收用户输入的整数数组（最多包含 10 个元素），并用冒泡排序将数组按从小到大的顺序排列。
排序后输出数组元素，数字之间用空格分隔。
如果用户输入的数字超过 10 个，只处理前 10 个数字，其余数字忽略。
如果数组已为空（用户输入的个数为 0），提示用户“数组为空，无法排序。”
*/

void bubble_sort(int arr[], int n)
{
	int j = 0;
	for (j = 0; j < n - 1; j++) //趟数
	{
		int k = 0;
		for (k = 0; k < n - 1 - j; k++) //每一趟走的步数
		{
			if (arr[k] > arr[k + 1])
			{
				int temp = arr[k + 1];
				arr[k + 1] = arr[k];
				arr[k] = temp;
			}
		}
	}
}





int main()
{
	printf("How many number do you want to process? > ");
	int n = 0;
	int arr[10];

	while (scanf("%d", &n) != 1)
	{
		printf("invalid input. Please check! > ");
		while (getchar() != '\n');
	}

	/*while (scanf("%d", &n) == 0)
	{
		printf("Your array is empty and can't be ranked.");
		while (getchar() != '\n');
	}
		这里不能用while是因为scanf没有扫到整数的时候返回的就是0；
		跟数字0产生了混淆，也影响了前面一个步骤的正常判断
	*/      

	if (n == 0)
	{
		printf("Your array is empty and can't be ranked.\n");
		return 0;
	}
	if (n > 10)
	{
		printf("That's too much! I will only process 10 of them. \n");
		n = 10; //top 10 figures
	}


	printf("Please enter your numbers:> ");
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]); //这后面不需要清除缓存区，不然输入的数字都没了
			}
	
	bubble_sort(arr, n);

	printf("Sorted array: ");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}