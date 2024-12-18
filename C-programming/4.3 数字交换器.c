#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void Swap(int* a, int* b)
{
	int z = * a;//z=a
	*a = *b; //a=b
	*b = z; //b=a

}


int main()
{
	int a = 0;
	int b = 0;
	printf("Please enter teo figure you want to swap:");
	
	
	while (scanf("%d %d", &a, &b) != 2) //ensure valid input
	{
		printf("Invalid input! Please check.\n");
		while (getchar() != '\n');
	}

	printf("This is your number before swapping: a=%d b=%d\n", a, b);
	Swap(&a, &b);
	printf("This is your number after swapping: a=%d b=%d", a, b);
	return 0;
}