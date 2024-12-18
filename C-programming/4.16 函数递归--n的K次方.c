#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
k>0 --> Pow(n,k)=n*Pow(n,k-1)
k=0 --> 1
k<0 --> 1.0/Pow(n,-k)

*/
double Pow(int n, int k)
{
	if (k > 0)
		return Pow(n, k - 1) * n;
	else if (k == 0)
		return 1;
	else if (k < 0)
		return 1.0 / Pow(n, k);
}


int main()
{
	int n = 0, k = 0;
	printf("enter number:> ");
	scanf("%d %d", &n, &k);
	double result=Pow(n, k);
	printf("Result: %.2f", result);


	return 0;
}