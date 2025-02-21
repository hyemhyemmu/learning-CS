#include <iostream>
using namespace std;

//  template specialization precedence
//  1. full template
//  2. overload template
//  3. specialized template


template<class T> void f(T) {
    //func1为基础模板
    cout<< "full template" <<endl;};
    template<class T> void f(T*) {
    //func2为func1的重载，仍是基础模板
    cout<< "full template -> overload template" <<endl;};
    template<> void f(char*) {
    //func3为func2的特化版本(T特化为char)
    cout<< "overload template -> specialized" <<endl;};

int main() {
    char *p;
    f(p);
    return 0;
}
