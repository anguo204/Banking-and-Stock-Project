#ifndef PROJECT2_BANKACCOUNTS_H
#define PROJECT2_BANKACCOUNTS_H
#include "Accounts.h"

//This is the bank account functions
class BankAccount : public Account {
public:
    BankAccount() :Account() {};
    BankAccount(double amount) :Account(amount) {};
    double deposit(double);
    bool withdraw(double);
private:
};





#endif //PROJECT2_BANKACCOUNTS_H
