#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int i = 0, n = 0;
	
	for (i = 1; i <= 9; i++)
	{
		for (n = 1; n <= i; n++)
		{
			printf("%d¡Á%d=%d ", i, n, i * n);
		}
		printf("\n");
		
	}


	return 0;
}