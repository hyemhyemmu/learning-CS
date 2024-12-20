#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

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

//Implement close, which takes two non - negative integers m and n.It returns whether m can be changed into n
//by either inserting one digit, removing one digit, or changing one digit.If m and n are the same number, they
//are not close.

int close(int m, int n)
{
	if (m < n)
	{
		int temp = 0;
		temp = m;
		m = n;
		n = temp;
	}
	while (m || n)
	{
		if (m % 10 == n % 10)
		{
			m = m / 10;
			n = n / 10;
		}
		else
		{
			return m / 10 == n || m / 10 == n / 10;
		}
	}
	return 0;
}


