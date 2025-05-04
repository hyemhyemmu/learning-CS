#include "linked_list_sort.h"

// 冒泡排序
int bubbleSort(Node** head, Node_compare cmp) {
    if (*head == NULL || (*head)->next == NULL) {
        return 0; // 空链表或只有一个节点，无需排序
    }
    
    int swapped;
    Node* current;
    Node* last = NULL;
    int swapCount = 0;
    
    do {
        swapped = 0;
        current = *head;
        
        while (current->next != last) {
            // 使用比较函数代替直接比较
            if (cmp(&current->data, &current->next->data) > 0) {
                // 交换数据而不是指针
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
                swapCount++;
            }
            current = current->next;
        }
        last = current;
    } while (swapped); // 一直swapped直到没得swapped了
    
    return swapCount;
}

// 归并排序辅助函数：分割链表
Node* splitList(Node* head) {
    Node* fast = head;
    Node* slow = head;
    Node* prev = NULL;
    
    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
    }
    
    if (prev != NULL) {
        prev->next = NULL;
    }
    
    return slow;
}

// 归并排序辅助函数：合并两个已排序链表，使用比较函数
Node* mergeLists(Node* a, Node* b, Node_compare cmp) {
    Node dummy;
    Node* tail = &dummy;
    dummy.next = NULL;
    
    while (a != NULL && b != NULL) {
        // 使用比较函数代替直接比较
        if (cmp(&a->data, &b->data) <= 0) {
            tail->next = a;
            a = a->next;
        } else {
            tail->next = b;
            b = b->next;
        }
        tail = tail->next;
    }
    
    tail->next = (a != NULL) ? a : b;
    
    return dummy.next;
}

// 归并排序实现，使用比较函数
Node* mergeSort(Node* head, Node_compare cmp) {
    if (head == NULL || head->next == NULL) {
        return head; // 基本情况：空链表或只有一个节点
    }
    
    // 分割链表为两半
    Node* middle = splitList(head);
    
    // 递归地对两半进行排序
    Node* left = mergeSort(head, cmp);
    Node* right = mergeSort(middle, cmp);
    
    // 合并两个已排序的链表
    return mergeLists(left, right, cmp);
}
