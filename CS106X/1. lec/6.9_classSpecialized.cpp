#include <iostream>
using namespace std;

// class template specialization precedence
// 1. Non-template function
// 2. Function template
// 3. Class template
// 4. Class template specialization

template <typename T1, typename T2>
class Sum{
public:
    Sum(T1 a, T2 b){
        cout << "Sum general: " << a + b << endl;
    }
};

// all specified
template <>
class Sum<int,int>{
public:
    Sum(int a, int b){
        cout << "Sum specialized: " << a + b << endl;
    }
};

// one specified
template <typename T>
class Sum<int,T>{
public:
    Sum(int a, T b){
        cout << "Sum one-specialized: " << a + b << endl;
    }
};

int main(){
    Sum<int,int> s1(10,20);
    Sum<float,float> s2(10.5,20.5);
    Sum<int,float> s3(10,20.5);
    return 0;
}
