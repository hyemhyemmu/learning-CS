#include "LInkedLIst.h"

void checkValid(void* p) {
	if (p == NULL) {
		perror("malloc failed");
		free(p);
		exit(EXIT_FAILURE);
	}
}


Deque* createNewDeque() {
	Deque* pDeque = (Deque*)malloc(sizeof(Deque));
	checkValid(pDeque);

	Node* sentinel = (Node*)malloc(sizeof(Node));
	checkValid(sentinel);

	sentinel->prev = sentinel;
	sentinel->next = sentinel;

	pDeque->sentinel = sentinel;
	pDeque->size = 0;

	return pDeque;
}

void addFront(Deque* deque, void* item) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	checkValid(newNode);
	
	Node* sentinel = deque->sentinel;

	newNode->item = item;
	newNode->next = sentinel->next;
	newNode->prev = sentinel;

	sentinel->next->prev = newNode;
	sentinel->next = newNode;

	deque->size++;
}


void addLast(Deque* deque, void* item) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	checkValid(newNode);

	Node* sentinel = deque->sentinel;

	newNode->item = item;
	newNode->prev = sentinel->prev;
	newNode->next = sentinel;

	sentinel->prev->next = newNode;
	sentinel->prev = newNode;

	deque->size++;
}


void** toList(Deque* deque) {
	int size = deque->size;
	Node* sentinel = deque->sentinel;
	Node* current = sentinel->next;
	void** list = (void**)malloc(sizeof(void*)*deque->size);

	for (int i = 0; i < size; i++) {
		list[i] = current->item;
		current = current->next;
	}

	return list;
}

int isEmpty(Deque* deque) {
	if (deque->size)
		return 0;
	return 1;
}

void* removeFirst(Deque* deque) {
	if (isEmpty)
		return NULL;
	Node* sentinel = deque->sentinel;
	void* removedItem = sentinel->next;
	
	Node* nextNode = sentinel->next->next;
	nextNode->prev = sentinel;
	sentinel->next = nextNode;

	deque->size--;
	return removedItem;
}

void* removeLast(Deque* deque) {
	if (isEmpty)
		return NULL;
	Node* sentinel = deque->sentinel;
	Node* last = sentinel->prev;
	void* removed = last->item;
	
	last->prev->next = sentinel;
	sentinel->prev = last->prev;
	deque->size--;
	return removed;
}


void* get(Deque* deque, int index) {
	if (index < 0 || index >= deque->size) {
		return NULL;
	}
	Node* current = deque->sentinel->next;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	return current->item;
}

void destroyDeque(Deque* deque) {
	while (!isEmpty(deque)) {
		removeFirst(deque);
	}
	free(deque->sentinel);
	free(deque);
}


int main() {
	
	Deque* deque = createNewDeque();
	int a = 10, b = 20, c = 30;

	addFirst(deque, &a);
	addLast(deque, &b);
	addFirst(deque, &c);


	int* item = (int*)get(deque, 1);
	if (item != NULL) {
		printf("Item at index 1: %d\n", *item); // Êä³ö£º20
	}

	item = (int*)removeLast(deque);
	if (item != NULL) {
		printf("Removed last item: %d\n", *item); // Êä³ö£º20
	}

	int size;
	void** list = toList(deque);
	printf("List contents:\n");
	for (int i = 0; i < deque->size; i++) {
		printf("%d ", *(int*)list[i]);
	}
	printf("\n");
	free(list); 

	destroyDeque(deque);

	return 0;
}