#include "6.5_ArrayStack.h"

ArrayStack::ArrayStack(){
    size = 0;
    capacity = 10;
    elements = new int[capacity];
}

void ArrayStack::checkCapacity(){
    if (size>=capacity){
        int *bigger = new int[capacity * capacity];
        for (int i = 0; i < size;i++){
            bigger[i] = elements[i];
        }
        delete[] elements;
        elements = bigger;
        capacity = capacity * capacity;
    }
}

ArrayStack::~ArrayStack(){
    delete[] elements;
}

// member functions
void ArrayStack::push(int n){
    checkCapacity();
    elements[size] = n;
    size++;
}


int ArrayStack::pop(){
    if(isEmpty()){
        cout << "The stack is empty!" << endl;
        return -1;
    }
    else
    {
        elements[size - 1] = 0;
        size--;
        return elements[size - 1];
    }
}
int ArrayStack::peek() const{
    if(isEmpty()){
        cout << "The stack is empty!" << endl;
        return -1;
    }
    return elements[size - 1];
}

bool ArrayStack::isEmpty() const{
    return !size;
}

ostream &operator<<(ostream &out, const ArrayStack &stack){
    out << "{";
    if (!stack.isEmpty()){
        out << stack.elements[0];
        for (int i = 1; i < stack.size;i++){
            out <<","<<stack.elements[i];
        }
    }
    out << "}";
    return out;
}
