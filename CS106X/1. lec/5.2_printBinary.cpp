#include <iostream>
using namespace std;

void printBinary(int n){
    if (n==0)
        return;
    printBinary(n / 2);

    cout << n % 2;
}

int main(){
    int num;
    cin >> num;
    printBinary(num);
}