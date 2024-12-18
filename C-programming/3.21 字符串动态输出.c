#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

int main()
{
	char arr1[] = "hello world!!!";
	char arr2[] = "##############";
	
	int left = 0;
	int right = strlen(arr2)-1; //=sizeof(arr2)/sizeof(arr2[0])

	while (left <= right)
	{
		arr2[left] = arr1[left];
		arr2[right] = arr1[right];
		printf("%s\n", arr2);
		Sleep(1000);
		system("cls");
		left++;
		right--;
	}

	return 0;
}