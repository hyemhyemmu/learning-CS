#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct Node
{
	struct Node* prev;
	void* item;
	struct Node* next;
}Node;

typedef struct Deque {
	struct Node* sentinel;
	int size;
} Deque;

//functions
//initialize
Deque* createNewDeque();

//add item to the front
void addFront(Deque* deque, void* item);

//add item to the back
void addLast(Deque* deque, void* item);

//collect items into a list
void** toList(Deque* deque);

//is empty
int isEmpty(Deque* deque);

//remove the first item
void* removeFirst(Deque* deque);


//remove the last item
void* removeLast(Deque* deque);


//get item at index
void* get(Deque* deque, int index);



//helper methods
void checkValid(void* p);
