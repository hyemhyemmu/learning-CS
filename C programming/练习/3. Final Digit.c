#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//
//Implement final_digit, which takes a non - negative integer n.As long as n has more than one digit, replace n
//with the sum of the digits of n.This process repeats until n becomes a single - digit number, which is returned.

int final_digit(int n)
{
	
	while (n >= 10) //continue to iterate if n>=10
	{
		int s = 0;
		while (n) //if n!=0
		{
			s += n % 10; //since value is changed after division, it is better to mod first then division
			n = n / 10;
			
		}
		n = s;
	}
	return n;
}




int main()
{
	int n = 0;
	printf("give me a number:>");
	scanf("%d", &n);

	int result = final_digit(n);
	printf("Here is the result: %d", result);

	return 0;
}