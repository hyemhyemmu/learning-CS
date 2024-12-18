#define _CRT_SECURE_NO_WARNINGS
//ASCII:73,32,97,99,110,32,100,111,32,105,116,33
#include <stdio.h>

int main()
{
	int arr[] = { 73,32,99,97,110,32,100,111,32,105,116,33 };
	int i = 0;
	int sz = sizeof(arr) / sizeof(arr[0]);

	while (i <= sz)
	{
		printf("%c", arr[i]);
		i++;
	}
	return 0;
}