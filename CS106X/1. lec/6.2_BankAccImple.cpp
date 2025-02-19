#include "6.2_BankAccount.h"
#include <iostream>

void BankAccount::deposit(double num){
    balance += num;
}

void BankAccount::getBalance(){
    cout << "current balance is: " << balance << endl;
}

BankAccount::BankAccount(string name, double balance) {
    this->name = name;
    this->balance = balance;
}