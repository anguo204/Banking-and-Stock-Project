#ifndef PROJECT2_STOCKSACCOUNT_H
#define PROJECT2_STOCKSACCOUNT_H
#include "Stocks.h"
class StockAccount : public Account {
private:
    BankAccount bankAccount;
    vector<Stock> stocksList;
    ifstream priceFiles[4];
    int numFiles;
    double searchFile(ifstream &, string, string &);
    void addStock(string, int);
    bool removeStock(string);
    void setBalance(double);
    int findStock(string);
    bool hasStock(string);
    void initPriceFiles(string[], int);


public:
    StockAccount(double, string[], int );
    BankAccount getBankAccount();
    void displayPortfolio();
    bool buyStock(string, double, int);
    bool sellStock(string, double, int);
    double getCurrentPrice(string, string &);
    bool withdraw(double);
    void deposit(double);
    void closeFiles();
};



#endif //PROJECT2_STOCKSACCOUNT_H
