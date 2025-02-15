#include <string>
#include <iostream>
using namespace std;

//This is pretty different from C, where strings are just arrays of characters.

string s = "Hello World!";

int main(){
    cout << s.at(0) << endl; // H
    cout << s[3] << endl; // l

    // ASCII values
    cout << (int)s.at(7) << endl; // 87
    return 0;
}
