#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
//冒泡排序优化 - 更通用、更普适

void Swap(char* p1, char* p2, int width)
{
	//逐个位交换地址
	char temp;
	int i = 0;
	for (i = 0; i < width; i++)
	{
		temp = *p1;
		*p1 = *p2;
		*p2 = temp;
	}
}


void bubble_sort(void* base, int sz,int width,int (*cmp)(const void*e1,const void*e2)) //cmp是比较函数
{
	int i = 0; //辅助指针
	int j = 0; //j表示趟数
	int flag = 0; //万一数组本身就是有序的
	for (j = 0; j < sz - 1; j++)
	{
		for (i = 0; i < sz - 1 - j; i++)
		{
			//前者大于后者时，交换
			if (cmp((char*)base + i * width, (char*)base + (i + 1) * width)) //要先想办法解引用 cmp(base+i,base+i+1)
			{
				Swap((char*)base + i * width, (char*)base + (i + 1) * width,width);
				flag = 1;
			}
			
		}
		if (flag == 0)
		{
			break;
		}
	}
	
}

struct Stu
{
	char name[20];
	int age;
};

int cmp_int(void* e1, void* e2)
{
	return (*(int*) e1 - *(int*) e2);  //强制转化为int类型的指针才能解引用
}

int cmp_stu_by_name(const void* e1, const void* e2)
{
	return strcmp(((struct Stu*)e1)->name, ((struct Stu*)e2)->name);
}

int main()
{
	int arr[] = { 9,7,3,2,1,5,6,7,8,9,2 };
	int i = 0;
	int sz = sizeof(arr) / sizeof(arr[0]);

	bubble_sort(arr, sz, sizeof(arr[0]), cmp_int);
	printf("排序数组：");
	for (i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	struct Stu s[] = { {"Messi,38"},{"Ronaldo",39},{"Yamal",17} };
	int sz_2 = sizeof(s) / sizeof(s[0]);
	bubble_sort(s, sz_2, sizeof(s[0]), cmp_stu_by_name);
	printf("排序结构体：");
	for (i = 0; i < sz_2; i++)
	{
		printf("%s %d ", s[i].name,s[i].age);
	}



	return 0;
}