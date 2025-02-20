#include "6.5_ArrayStack.h"
#include "6.5_ArrayStack.cpp"

int main() {
    ArrayStack stack;
    
    // 测试 push
    stack.push(1);
    stack.push(2);
    stack.push(3);
    cout << "After pushing 1,2,3: " << stack << endl;
    
    // 测试 pop
    cout << "Popped value: " << stack.pop() << endl;
    cout << "After pop: " << stack << endl;
    
    // 测试 peek
    cout << "Peek value: " << stack.peek() << endl;
    
    // 测试 isEmpty
    cout << "Is empty? " << (stack.isEmpty() ? "yes" : "no") << endl;
    
    return 0;
}
