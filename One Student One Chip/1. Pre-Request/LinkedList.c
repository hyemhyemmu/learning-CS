#include "LinkedList.h"

List *List_create(){
    ListNode *newNode = calloc(1, sizeof(List));
    if (newNode == NULL)
        printf(errno);
    else
        return newNode;
}