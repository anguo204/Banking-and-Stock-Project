#ifndef PROJECT2_STOCKS_H
#define PROJECT2_STOCKS_H
#include "BankAccounts.h"

/***This is the stock that will store all the stocks that was bought into the vector I created this
 * file so its easier to keeptrack of all the functions that I can use to see the stocks that was bought*****/
class Stock {
private:
    string symbol;
    int quantity;

public:
    Stock() { symbol = ""; quantity = 0; }
    Stock(string, int);
    int getQuantity();
    void setQuantity(int);
    string getSymbol();
    void setSymbol(string);
};

#endif //PROJECT2_STOCKS_H
