#ifndef LINKED_LIST_SORT_H
#define LINKED_LIST_SORT_H

#include <stdio.h>
#include <stdlib.h>

// 链表节点结构
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 比较函数
typedef int (*Node_compare)(const void *a, const void *b);

// 排序算法
int bubbleSort(Node** head, Node_compare cmp);
Node* mergeSort(Node* head, Node_compare cmp);

#endif // LINKED_LIST_SORT_H
