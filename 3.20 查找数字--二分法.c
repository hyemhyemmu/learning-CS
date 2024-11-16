#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
	int n = 0;
	printf("请输入你要查找的数字：");
	scanf("%d", &n);

	
	int sz = sizeof(arr) / sizeof(arr[0]);
	
	int in_left = 0;
	int in_right = sz - 1;
	
	
	while (in_left <= in_right)
	{
		int in_mid = (in_left + in_right) / 2;
		
		if (arr[in_mid] < n)
		{
			in_left = in_mid + 1;
		}
		else if (arr[in_mid] > n)
		{
			in_right = in_mid - 1;
		}
		else if (arr[in_mid] == n)
		{
			printf("找到了！他在位置%d", in_mid + 1);
			break;
		}

	}
	if (in_left > in_right)
	{
		printf("糟糕，你的数字不在数组里哦！");
	}
	


	return 0;
}