#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	// & (AND)
	int a1 = 5;  //0000101����
	int b1 = -7; //1000111ԭ�� 1111000���� 1111001����
	int c1 = a1 & b1; //����0000001 (1)
	printf("c1=%d\n", c1);

	// | (OR)
	int a2 = 5;  //0000101����
	int b2 = -7; //1000111ԭ�� 1111000���� 1111001����
	int c2 = a2 | b2; //����1111100 ����1111100 ԭ��1000011 (-3)
	printf("c2=%d\n", c2);

	// ^ (XOR)
	int a3 = 5;  //0000101����
	int b3 = -7; //1000111ԭ�� 1111000���� 1111001����
	int c3 = a3 ^ b3; //����1111100 ����1111011 ԭ��1000100 (-4) 
	printf("c3=%d\n", c3);







	return 0;
}