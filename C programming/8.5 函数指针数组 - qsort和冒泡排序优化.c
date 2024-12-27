//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//
////迭代方法 - 基础版本
//void bubble_sort(int* arr, int sz)
//{
//	int i = 0; //辅助指针
//	int j = 0; //j表示趟数
//	for (j = 0; j < sz - 1; j++)
//	{
//		for (i = 0; i < sz - 1 - j; i++)
//		{
//			//如果大于，交换数字，指针跳转
//			if (arr[i] > arr[i + 1])
//			{
//				int temp = 0;
//				temp = arr[i];
//				arr[i] = arr[i + 1];
//				arr[i + 1] = temp;
//			}
//		}
//
//	}
//	
//}
//
//
////递归方法
//void bubble_sort_2(int* arr, int sz)
//{
//	if (sz == 1)
//	{
//		return;
//	}
//	int i = 0;
//	
//	//比较方式是一样的
//	for (i = 0; i < sz - 1; i++)
//	{
//		//如果大于，交换数字，指针跳转
//		if (arr[i] > arr[i + 1])
//		{
//			int temp = 0;
//			temp = arr[i];
//			arr[i] = arr[i + 1];
//			arr[i + 1] = temp;
//		}
//	}
//
//	bubble_sort_2(arr, sz - 1);
//}
//
//
////优化方法 - qsort 
//int comp_int(void* e1, void* e2)
//{
//	return (*(int*) e1 - *(int*) e2);  //强制转化为int类型的指针才能解引用
//}
//
//
//
//int main()
//{
//	int arr[] = { 9,7,3,2,1,5,6,7,8,9,2 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//
//	bubble_sort(arr,sz);
//
//	int i = 0;
//	printf("使用迭代方法：");
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	printf("\n");
//
//	int arr_2[] = { 9,7,3,2,1,5,6,7,8,9,2 };
//	bubble_sort_2(arr_2, sz);
//	printf("使用递归方法：");
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", arr_2[i]);
//	}
//	printf("\n");
//
//	int arr_3[] = { 9,7,3,2,1,5,6,7,8,9,2 };
//	qsort(arr_3, sz, sizeof(arr[0]), comp_int);  //起始，个数，元素大小，比较函数（自定义) - 要是一个接受两个void，返回int的函数
//	printf("使用qsort方法：");
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", arr_3[i]);
//	}
//	return 0;
//}