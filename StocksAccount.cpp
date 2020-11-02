#include "StocksAccount.h"

StockAccount::StockAccount(double initialAmount, string priceFileNames[], int n) :Account(initialAmount){
    bankAccount = BankAccount(initialAmount);
    stocksList = vector<Stock>();
    initPriceFiles(priceFileNames, n);
}

void StockAccount::setBalance(double amount) {
    Account::setBalance(amount);
    bankAccount.setBalance(amount);
}

void StockAccount::displayPortfolio() {
    double price, tempTotal, grandTotal = 0;
    string string1;
    int qty;
    cout << "\n\tCash balance = $" << fixed << setprecision(2) << getBalance() << endl;
    cout << "\n\tSymbol\t\tCompany\t\t\t\t\tNumber\t\tPrice\t\tTotal" << endl << endl;
    for (int i = 0; i<stocksList.size(); i++) {
        price = getCurrentPrice(stocksList[i].getSymbol(), string1);
        qty = stocksList[i].getQuantity();
        tempTotal = price * qty;
        grandTotal += tempTotal;
        cout << "\t" << stocksList[i].getSymbol() << "\t\t";
        cout.width(30);
        cout << left << string1 << "\t\t" << qty << "\t\t$" << price << "\t\t$" << tempTotal << endl;
    }
    grandTotal += getBalance();

    cout << "\n\n\tTotal portfolio value: $" << grandTotal << endl;

}

bool StockAccount::removeStock(string symbol) {
    for (vector<Stock>::iterator i = stocksList.begin(); i != stocksList.end(); ++i) {
        if ((*i).getSymbol() == symbol) {
            stocksList.erase(i);
            return true;
        }
    }
    return false;
}

void StockAccount::deposit(double amount) {
    setBalance(getBalance() + amount);
}

bool StockAccount::withdraw(double amount){
    if (bankAccount.withdraw(amount)) {
        Account::setBalance(bankAccount.getBalance());
        return true;
    }
    else {
        return false;
    }
}

bool StockAccount::sellStock(string sym, double sellPrice, int qty) {
    int holdNum = findStock(sym);
    string name;
    double price;
    if (holdNum == -1) {
        cout << "\n\tCannot process transaction. No shares of " << sym << " in portfolio." << endl << endl;
        return false;
    }

    if (qty >stocksList[holdNum].getQuantity()) {
        cout << "\n\tCannot process transaction. Not enough shares of " << sym << " in portfolio." << endl << endl;
        return false;
    }
    else {
        price = getCurrentPrice(sym, name);
        if (sellPrice > price) {
            cout << "\n\tCannot process transaction. Sell price  $" << sellPrice << " is larger than current price $" << price << endl << endl;
            return false;
        }
        else {
            double total = sellPrice * qty;
            stocksList[holdNum].setQuantity(stocksList[holdNum].getQuantity() - qty);
            setBalance(getBalance() + total);
            if (stocksList[holdNum].getQuantity() == 0) {
                removeStock(sym);
            }
            return true;
        }
    }
}

void StockAccount::addStock(string sym, int qty) {
    int holdNum = findStock(sym);
    if (holdNum == -1) {
        cout << " " << endl;
        Stock s = Stock(sym, qty);
        stocksList.push_back(s);
    }
    else {
        stocksList[holdNum].setQuantity(stocksList[holdNum].getQuantity() + qty);
    }
}

bool StockAccount::hasStock(string sym) {
    for (int i = 0; i<stocksList.size(); i++) {
        if (stocksList[i].getSymbol() == sym) {
            return true;
        }
    }
    return false;
}

int StockAccount::findStock(string sym){
    for (int i = 0; i<stocksList.size(); i++) {
        if (stocksList[i].getSymbol() == sym) {
            return i;
        }
    }
    return -1;
}



BankAccount StockAccount::getBankAccount() {
    return bankAccount;
}

bool StockAccount::buyStock(string sym, double buyPrice, int quantity) {
    string name;
    double price = getCurrentPrice(sym, name);
    double total = buyPrice * quantity;

    if (name.empty()) {
        cout << "\n\tCannot process transaction. No such symbol: " << sym << endl << endl;
        return false;
    }
    else if (buyPrice < price) {
        cout << "\n\tCannot process transaction. Buy price $" << buyPrice << " is less than current price $" << price << endl << endl;
        return false;
    }
    else if (total > getBalance()) {
        cout << "\n\tCannot process transaction. Insufficient Balance." << endl << endl;
        return false;
    }
    else {
        addStock(sym, quantity);
        setBalance(getBalance() - total);
        return true;
    }
}

double StockAccount::getCurrentPrice(string sym, string &name) {
    int randomFile = rand() % numFiles;
    return searchFile(priceFiles[randomFile], sym, name);
}


double StockAccount::searchFile(ifstream &file, string symbol, string &name) {
    string sym;
    double price;
    string company;
    string line, t;

    file.clear();
    file.seekg(0, ios::beg);
    while (file >> sym) {
        if (sym != symbol)
            continue;
        company = "";
        while (file >> t) {
            if (t.find_first_not_of("0123456789.") != string::npos)
                company += " " + t;
            else {

                name = company;
                price = atof(t.c_str());
                return price;
            }
        }
    }
    name = "";
    return 0;
}

void StockAccount::initPriceFiles(string filenames[], int n) {
    numFiles = n;
    srand(time(NULL));
    for (int i = 0; i<n; i++) {
        priceFiles[i].open(filenames[i].c_str());
        if (!priceFiles[i].is_open()) {
            cout << "\n\tError opening file " << filenames[i] << endl << endl;
            exit(1);
        }
    }
}

void StockAccount::closeFiles() {
    for (int i = 0; i<numFiles; i++) {
        priceFiles[i].close();
    }
}

