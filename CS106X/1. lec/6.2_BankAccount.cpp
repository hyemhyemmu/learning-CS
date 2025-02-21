#include "6.2_BankAccount.h"
#include "6.2_BankAccImple.cpp"
#include <iostream>

int main(){
    BankAccount acc1 ("William", 100.00);
    acc1.deposit(1000.99);
    cout << acc1 << endl;
    return 0;
}
