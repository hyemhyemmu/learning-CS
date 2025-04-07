#include "LinkedList.h"

List *List_create(){
    ListNode *newNode = calloc(1, sizeof(List));
    if (newNode == NULL)
        printf(errno);
    else
        return newNode;
}

void List_destroy(List *list){
    LIST_FOREACH(list, first, next, curr){
        if (curr->prev){
            free(curr->prev);
        }
    }
    free(list->last);
    free(list);
}


void List_clear(List *list){
    LIST_FOREACH(list, first, next, curr){
        free(curr->next);
    }
}

void List_clear_destroy(List *list){
    List_clear(list);
    List_destroy(list);
}

void List_push(List *list, void *value){
    // 一直遍历到末尾
    LIST_FOREACH(list, first, next, curr){
        if (!curr->next){
            ListNode *newNode = calloc(1, sizeof(List));
            if (newNode == NULL)
                printf(errno);
            else{
                newNode->value = value;
                newNode->prev = curr;
                newNode->next = NULL;
                curr->next = newNode;
                list->count++;
            }
        }
    }
}
