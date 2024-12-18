#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void reverse(char* arr,int size)
{
	int left = 0;
	int right = size - 1;

	while (left < right)
	{
		int temp = 0;
		temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
		left++;
		right--;
	}
}


int main()
{
	printf("Please enter a string: ");
	char arr[100] = { 0 };
	
	gets(arr);

	int sz = sizeof(arr) / sizeof(arr[0]);

	reverse(arr,sz);
	
	int i = 0;
	for (i = 0; i < sz; i++)
	{
		printf("%c", arr[i]);
	}


	return 0;
}