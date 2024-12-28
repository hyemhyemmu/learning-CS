#pragma once
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

//动态原则：默认存放3个人的信息；如果不够了，一次增加2个联系人的容量
#define DEFAULT_SZ 3 //默认初始容量
#define DEFAULT_INC 2 //默认单次增加容量
#define MAX 100 //定义最大联系人量为100
#define MAX_NAME 50
#define MAX_SEX 5
#define MAX_TEL 20
#define MAX_ADDR 60


//声明类型 - 每一个人的信息
typedef struct PeoInfo
{
	char name[MAX_NAME];
	int age;
	char sex[MAX_SEX];
	char tel[MAX_TEL];
	char addr[MAX_ADDR];

} PeoInfo;


//整个通讯录
typedef struct Contact
{
	PeoInfo* data;
	int count; //记录当前通讯录的实际人数
	int capacity; //当前通讯录的容量
}Contact;


//初始化函数
int InitContact(Contact* pc);

//回收空间
void DestroyContact(Contact* pc);

//增加联系人
void AddContact(Contact* pc);

//打印通讯录中的信息
void ShowContact(const Contact* pc);

//查找联系人，返回索引
int FindByName(Contact* pc);

//删除联系人
void DelContact(Contact* pc);

//查找并打印联系人
void SearchContact(Contact* pc);

//修改指定联系人信息
void ModifyContact(Contact* pc);

//排序
void SortContact(Contact* pc);