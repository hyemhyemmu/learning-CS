#include "6.2_BankAccount.h"
#include <iostream>

void BankAccount::deposit(double num){
    balance += num;
}

void BankAccount::getBalance() const{
    cout << "current balance is: " << balance << endl;
}

BankAccount::BankAccount(string name, double balance) {
    this->name = name;
    this->balance = balance;
}

bool operator==(const BankAccount &acc1, const BankAccount& acc2){
    return acc1.name == acc2.name && acc1.balance == acc2.balance;
}
