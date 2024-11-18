//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <math.h>
//
////输出1-100的质数
//
//
//int main()
//{
//	int i = 0;
//	int count = 0;
//	for (i = 2; i <= 100; i++) //从2开始，因为1不是质数
//	{
//		int flag = 1; //用一个flage来提示输出（关键！）
//		int j = 0;
//		for (j = 2; j <= i-1; j++) //优化，使用sqrt(i)
//		{
//			if (i % j == 0)
//			{
//				flag = 0;
//				break; //从最近的循环体，也就是for跳出 
//			}
//
//		}
//		if (flag == 1) //完成所有数字的试除后才能判断为质数
//		{
//			
//			count++;
//			printf("%d ", i);
//		}
//	}
//	printf("\nThere are %d numbers.", count);
//
//
//
//	return 0;
//}