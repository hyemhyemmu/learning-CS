#define _CRT_SECURE_NO_WARNINGS
#include "system.h"

//初始化系统
int Init(System* sys)
{
	assert(sys);
	
	sys->count = 0;
	sys->data = (StuInfo*)calloc(DEFAULT_SYS_CAPACITY, sizeof(StuInfo));
	if (sys->data == NULL)
	{
		printf("%s\n", strerror(errno));
		return 1;
	}
	sys->capacity = DEFAULT_SYS_CAPACITY;
	return 0;
}


//检查系统是否为空
int CheckIfEmpty(System* sys)
{
	if (sys->count == 0)
	{
		printf("系统为空！");
		return 1;
	}
	return 0;
}



//检查容量，必要时扩容
void CheckCapacity(System* sys)
{
	if (sys->capacity == sys->count)
	{
		StuInfo* temp = (StuInfo*)realloc(sys->data, (DEFAULT_INC + sys->capacity) * sizeof(StuInfo));
		if (temp == NULL)
		{
			printf("%s\n", strerror(errno));
			return;
		}
		sys->data = temp;
		sys->capacity += DEFAULT_INC;
	}
}


//添加
void AddStu(System* sys)
{
	assert(sys);
	CheckCapacity(sys);

	printf("请输入姓名：>");
	scanf("%s", sys->data[sys->count].name);
	printf("请输入学号：>");
	scanf("%d", &(sys->data[sys->count].stu_num));
	printf("请输入成绩：>");
	scanf("%d", &(sys->data[sys->count].grade));

	sys->count++;
	printf("增加成功！\n");
}

//通过名字查找，返回索引
int FindByName(const System* sys)
{

	char name[] = { 0 };
	printf("请输入要查找的学生姓名：>");
	fgets(name, MAX_NAME, stdin);
	name[strcspn(name, "\n")] = 0;

	int i = 0;
	for (i = 0; i < sys->count; i++)
	{
		if (strcmp(sys->data[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;
}


//删除指定学生信息
void DelStu(System* sys)
{
	assert(sys);
	if (CheckIfEmpty(sys))
	{
		return 1;
	}
	
	int index = FindByName(sys);
	if (index == -1)
	{
		printf("此人不存在！");
		return;
	}

	//通过覆盖来模拟删除
	int i = 0;
	for (i = index; i < sys->count - 1; i++)
	{
		sys->data[i] = sys->data[i + 1];
	}
	sys->count--;
	printf("删除成功！现在还有%d个学生\n", sys->count);

}

//查找学生并打印
void SearchStu(const System* sys)
{
	assert(sys);
	if (CheckIfEmpty(sys))
	{
		return 1;
	}

	int index = FindByName(sys);
	if (index == -1)
	{
		printf("此人不存在！");
		return;
	}

	//打印联系人信息
	printf("%-10s\t%-10s\t%-10s\n", "名字", "学号", "成绩");
	printf("%-10s\t%-10d\t%-10d\n",
		sys->data[index].name,
		sys->data[index].stu_num,
		sys->data[index].grade);
}

//退出系统，释放内存
void Exit(System* sys)
{
	if (sys->data)
	{
		free(sys->data);
		sys->data = NULL;
	}
}