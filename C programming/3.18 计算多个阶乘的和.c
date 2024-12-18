//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//
////打印多个阶乘
//int main()
//{
//	int i = 0;//as input
//	int m = 1;//initial
//	int n = 1;//start calculating
//	int add = 1;//初始化必须为1，因为后面做的是乘法
//	int sum = 0;
//
//	printf("你想要1到几的阶乘的和？");
//	scanf("%d", &i);
//
//	for (m = 1; m <= i; m++)
//	{
//		add = 1; //关键：需要重新重置为1，都
//		for (n = 1; n <= m; n++)
//		{
//			add = add * n;
//		}
//		sum = add + sum;
//	}
//	printf("Final answer is: %d", sum);
//	
//	
//	return 0;
//}
