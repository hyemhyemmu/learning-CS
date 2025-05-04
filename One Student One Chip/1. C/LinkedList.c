#include "LinkedList.h"

List *List_create(){
    ListNode *newNode = calloc(1, sizeof(ListNode));
    if (newNode == NULL){
        fprintf(stderr, "Out of memory.\n");
        errno = ENOMEM;
        return NULL;
    }
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

// // 一个较为低效的解法：逐个遍历
// void List_push(List *list, void *value){
//     // 一直遍历到末尾
//     LIST_FOREACH(list, first, next, curr){
//         if (!curr->next){
//             ListNode *newNode = calloc(1, sizeof(ListNode));
//             if (newNode == NULL)
//                 printf(errno);
//             else{
//                 newNode->value = value;
//                 newNode->prev = curr;
//                 newNode->next = NULL;
//                 curr->next = newNode;
//                 list->count++;
//             }
//         }
//     }
// }


// 一个更高效的实现
void List_push(List *list, void *value){
    ListNode * newNode = calloc(1, sizeof(ListNode));
    if (newNode == NULL){
        fprintf(stderr, "Out of Memory");
        errno = ENOMEM;
        return;
    }

    newNode->value = value;

    if (list->last == NULL){
        // list is empty
        list->first = newNode;
        list->last = newNode;
    }else{
        list->last->next = newNode;
        newNode->prev = list->last;
        list->last = newNode;
    }

    list->count++;
}

void *List_remove(List *list, ListNode *node){
    // check validation
    if (list->count == 0 || list == NULL){
        fprintf(stderr, "The list is empty");
        return NULL;
    }
    if (node == NULL){
        fprintf(stderr, "The node is invalid");
        return NULL;
    }

    void *result = node->value;

    // only one element
    if (node == list->first && node == list->last){
        list->first = NULL;
        list->last = NULL;
    }

    // head 
    else if (node == list->first){
        ListNode *predessesor = node->next;
        predessesor->prev = NULL;
        list->first = predessesor;
    }

    // last
    else if (node == list->last){
        ListNode *predessesor = node->prev;
        predessesor->next = NULL;
        list->last = predessesor;
    }

    // middle 
    else{
        ListNode *next = node->next;
        ListNode *prev = node->prev;
        prev->next = next;
        next->prev = prev;
    }

    list->count--;
    free(node);
    return result;
}

void *List_pop(List *list){
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value){
    ListNode * newNode = calloc(1, sizeof(ListNode));
    if (newNode == NULL){
        fprintf(stderr, "Out of Memory");
        errno = ENOMEM;
        return;
    }

    newNode->value = value;

    if (list == NULL || list->count == NULL){
        // list is empty
        list->first = newNode;
        list->last = newNode;
    }else{
        list->first->prev = newNode;
        newNode->next = list->first;
        list->first = newNode;
    }

    list->count++;
}

void *List_shift(List *list){
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}
