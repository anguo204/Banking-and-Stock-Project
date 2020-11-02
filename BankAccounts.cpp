#include "BankAccounts.h"

//This is the function of the Bank Account menu with the option of deposit and withdraw
double BankAccount::deposit(double money) {
    setBalance(getBalance() + money);
    return getBalance();
}

bool BankAccount::withdraw(double money) {
    if (money < getBalance()) {
        setBalance(getBalance() - money);
        return true;
    }
    else {
        return false;
    }
}
