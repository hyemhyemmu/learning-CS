#ifndef _bankaccount_h
#define _bankaccount_h
#include <string>
using namespace std;

class BankAccount{
public:
    BankAccount(string name,double balance);
    void deposit(double num);
    void getBalance() const;

private:
    string name;
    double balance;
};

#endif
