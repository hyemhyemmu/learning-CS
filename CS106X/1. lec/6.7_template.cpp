#include <iostream>
using namespace std;

// topic: template
// template is a feature of C++ that allows us to write a single function/class to work with different data types

/**
 * template function
 */
template <typename T>
void mySwap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

void test01() {
    int a = 10;
    int b = 20;
    
    cout << "Before swap:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    
    mySwap(a, b);  // this is automatically deduced
    
    cout << "\nAfter swap:" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
}

/**
 * template can be specified explicitly
 */
template<class T>
T div2(const T &a) {
    cout << "using template!" << endl;
    return a / 2;
}

template<>
int div2(const int&a){
    cout << "better solution!" << endl;
    return a >> 1;
}


int main() {
    test01();
    cout << "--------------------" << endl;
    cout<<div2(1.5) << endl;
    cout<<div2(2) << endl;
    return 0;
}