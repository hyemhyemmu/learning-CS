#define _CRT_SECURE_NO_WARNINGS
#include "contact.h"

//初始化
int InitContact(Contact* pc)
{
	assert(pc);
	pc->count = 0;
	pc->data=(PeoInfo*)calloc(DEFAULT_SZ, sizeof(PeoInfo)); //初始化3个人的空间
	if (pc->data == NULL)
	{
		printf("InitContact: %s\n", strerror(errno));
		return 1;
	}
	pc->capacity = DEFAULT_SZ;
	return 0;
}

//容量检查函数
void CheckCapacity(Contact* pc)
{
	if (pc->count == pc->capacity)
	{
		PeoInfo* temp = (PeoInfo*)realloc(pc, (DEFAULT_INC + pc->capacity) * sizeof(PeoInfo));
		if (temp == NULL)
		{
			printf("AddContact: %s\n", strerror(errno));
			return;
		}
		pc->data = temp;
		pc->capacity += DEFAULT_INC;
	}
}


//增加联系人
void AddContact(Contact* pc)
{
	assert(pc);
	
	//容量不够时增容
	CheckCapacity(pc);

	printf("请输入名字：>");
	scanf("%s", pc->data[pc->count].name);
	printf("请输入年龄：>");
	scanf("%d", &(pc->data[pc->count].age));
	printf("请输入性别：>");
	scanf("%s", pc->data[pc->count].sex);
	printf("请输入电话：>");
	scanf("%s", pc->data[pc->count].tel);
	printf("请输入地址：>");
	scanf("%s", pc->data[pc->count].addr);

	pc->count++;
	printf("增加成功！\n");

}

//展示通讯录
void ShowContact(const Contact* pc) 
{
	if (pc->count == 0)
	{
		printf("通讯录为空！");
		return;
	}
	int i = 0;
	printf("%20s\t%5s\t%5s\t%12s\t%30s\n", "名字", "年龄", "性别", "电话", "地址");
	for (i = 0; i < pc->count; i++)
	{
		printf("%20s\t%3d\t%5s\t%12s\t%30s\n",	pc->data[i].name, 
												pc->data[i].age,
												pc->data[i].sex,
												pc->data[i].tel,
												pc->data[i].addr);
	}
}


//查找联系人
int FindByName(Contact* pc)
{
	assert(pc);

	char name[MAX_NAME] = { 0 };
	printf("请输入名字:>");
	int i = 0;
	for (i = 0; i < MAX_NAME; i++)
	{
		scanf("%s", &name[i]);
	}

	for (i = 0; i < pc->count; i++)
	{
		if (strcmp(name, pc->data[i].name) == 0)
		{
			return i;
		}
	}
	return -1;
	
}


//删除联系人
void DelContact(Contact* pc)
{
	if (pc->count == 0)
	{
		printf("通讯录为空！");
		return;
	}
	int pos = FindByName(pc);
	if (pos == -1)
	{
		printf("查无此人");
		return;
	}
	//删除 - 通过覆盖来模拟删除
	int i = 0;
	for (i = pos; i < pc->count - 1; i++)  //防止越界，所以减一
	{
		pc->data[i] = pc->data[i + 1];
	}
	pc->count--;
	printf("删除成功！现在还有%d个联系人\n", pc->count);
}



//查找并打印联系人
void SearchContact(Contact* pc)
{
	assert(pc);
	if (pc->count == 0)
	{
		printf("通讯录为空！");
		return;
	}
	int index = FindByName(pc);
	if (index == -1)
	{
		printf("此人不存在！");
		return;
	}

	//打印联系人信息
	printf("%20s\t%5s\t%5s\t%12s\t%30s\n", "名字", "年龄", "性别", "电话", "地址");
	
	printf("%20s\t%3d\t%5s\t%12s\t%30s\n", pc->data[index].name,
		pc->data[index].age,
		pc->data[index].sex,
		pc->data[index].tel,
		pc->data[index].addr);
}


//修改指定联系人信息
void ModifyContact(Contact* pc)
{
	assert(pc);
	if (pc->count == 0)
	{
		printf("通讯录为空！");
		return;
	}
	int index = FindByName(pc);
	if (index == -1)
	{
		printf("此人不存在！");
		return;
	}

	printf("找到啦,现在输入新的信息吧!");
	printf("请输入名字：>");
	scanf("%s", pc->data[index].name);
	printf("请输入年龄：>");
	scanf("%d", &(pc->data[index].age));
	printf("请输入性别：>");
	scanf("%s", pc->data[index].sex);
	printf("请输入电话：>");
	scanf("%s", pc->data[index].tel);
	printf("请输入地址：>");
	scanf("%s", pc->data[index].addr);

	printf("修改成功\n");

}

//排序函数
int cmp_by_name(const void* e1, const void* e2)
{
	return strcmp(((PeoInfo*)e1)->name, ((PeoInfo*)e2)->name);
}

//排序
void SortContact(Contact* pc)
{
	assert(pc);
	if (pc->count == 0)
	{
		printf("通讯录为空！");
		return;
	}
	qsort(pc->data, pc->count, sizeof(PeoInfo), cmp_by_name);
	printf("排序成功！");
}

//回收空间
void DestroyContact(Contact* pc)
{
	assert(pc);
	free(pc->data);
	pc->data = NULL;
}