#ifndef PROJECT2_ACCOUNT_H
#define PROJECT2_ACCOUNT_H

using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <iomanip>
#include <ctime>
#include <cctype>

//This is the main account class
class Account {
private:
    double cashbalance;

public:
    Account() { cashbalance = 0; }
    Account(double);
    double getBalance();
    void setBalance(double);

};

#endif //PROJECT2_ACCOUNT_H
