#include <iostream>
using namespace std;

class LinkedList{
public:
    LinkedList(int val) : value(val), next(nullptr) {}
    int value;
    LinkedList* next;
};

int main(){
    LinkedList *node1 = new LinkedList(42);
    node1->next = new LinkedList(36);
    node1->next->next = nullptr;
    delete node1->next;
    delete node1;
    return 0;
}