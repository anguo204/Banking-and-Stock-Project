#include "Accounts.h"

Account::Account(double balance) {
    cashbalance = balance;
}

double Account::getBalance() {
    return cashbalance;
}

void Account::setBalance(double amount) {
    cashbalance = amount;
}


