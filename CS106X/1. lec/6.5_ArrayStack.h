#ifndef _arraystack_h
#define _arraystack_h
#include <iostream>
using namespace std;

class ArrayStack{
public:
    ArrayStack();
    ~ArrayStack();

    // member functions
    void push(int n);
    int pop();
    int peek() const;
    bool isEmpty() const;
    friend ostream &operator<<(ostream &out, const ArrayStack &stack);

private:
    int *elements; // an array to store the stuff
    int size;
    int capacity;
    void checkCapacity();
};

#endif
