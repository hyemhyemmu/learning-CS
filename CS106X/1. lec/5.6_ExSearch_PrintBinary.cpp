#include <iostream>
#include <string>
using namespace std;

// pretty different from the usual syntax of recursion
// but really important big idea
void printBinary(int digits, string prefix){
    if (digits==0)
        cout << prefix << endl;
    else{
        printBinary(digits - 1, prefix + '0');
        printBinary(digits - 1, prefix + '1');
    }
}
