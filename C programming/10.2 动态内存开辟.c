#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main()
{
	//¾²Ì¬¿ª±Ù
	int arr[40];

	//¶¯Ì¬¿ª±Ù
	int* p = (int*)malloc(10);

	if (p == NULL)
	{
		printf("%s\n", strerror(errno));
		return 1;
	}

	int i = 0;
	for (i = 0; i < 10; i++)
	{
		*(p + i) = i;
		printf("%d ", *(p + i));
	}

	free(p);
	p = NULL;

	return 0;
}