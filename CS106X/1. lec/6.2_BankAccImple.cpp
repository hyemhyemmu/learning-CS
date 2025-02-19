#include "6.2_BankAccount.h"
#include <iostream>

void BankAccount::deposit(double num){
    balance += num;
}

double BankAccount::getBalance() const{
    return balance;
}

BankAccount::BankAccount(string name, double balance) {
    this->name = name;
    this->balance = balance;
}

bool operator==(const BankAccount &acc1, const BankAccount& acc2){
    return acc1.name == acc2.name && acc1.balance == acc2.balance;
}

string BankAccount::getName() const{
    return name;
}

ostream& operator <<(ostream& out, const BankAccount acc){
    out << acc.getName() << " has " << " $" << acc.getBalance();
    return out;
}
