/***Andy Guo 172004093
 * PM Project #2
 * 5/5/2018
 *********************/
#include "StocksAccount.h"

//This makes sure that the string is acceptable
string toUpper(string str) {
    string upper = "";
    for (int i = 0; i < str.size(); i++) {
        upper.append(1, toupper(str[i]));
    }
    return upper;
}

//This will check to see if the user enters a number for the menu
bool isItANumber(string &value) {
    if (value.find_first_not_of("0123456789.") == string::npos) {
        return false;
    }
    else
        return true;
}

//This will read and print out everything in the transaction txt file.
void displayTransactionHistory(fstream &file) {
    string line;
    file.clear();
    file.seekg(0, ios::beg);
    while (!file.eof()) {
        getline(file, line);
        cout << "\n\t" << line;
    }
    cout << endl;
}

//This opens up the stock menu if the user choices this one
void stockMenu(StockAccount &account, istream &input, fstream &stockTransaction) {
    int c, q; //c is the choice you decided and q is the quality
    string sym, company;
    double price, currentPrice;
    string d;//d is the input that you entered
    time_t now;
    tm* t1;
    while (true) {
        cout << "\n\t 1. Display current price for a stock symbol" << endl;
        cout << "\t 2. Buy stock" << endl;
        cout << "\t 3. Sell stock" << endl;
        cout << "\t 4. Display current portfolio" << endl;
        cout << "\t 5. Display transactions history" << endl;
        cout << "\t 6. Return to main menu" << endl;
        cout << "\t Your selection: ";

        input >> d;
        if (isItANumber(d)) {
            cout << "\tInvalid input!" << endl;
            continue;
        }
        else
            c = atoi(d.c_str());

        if (c == 1) {
            cout << "\n\tEnter stock symbol for checking price: ";
            input >> sym;
            sym = toUpper(sym);
            currentPrice = account.getCurrentPrice(sym, company);
            if (company.empty()) {
                cout << "\n\tInvalid sym!\n";
            }
            else
            {
                now = time(0);
                t1 = localtime(&now);
                cout << "\n\t" << sym << "\t" << company << "\t$" << currentPrice << "\t" << t1->tm_hour << ":" << t1->tm_min << ":" << t1->tm_sec << endl;
            }
        }

        else if (c == 2) {
            cout << "\n\tEnter buy options: ";
            input >> sym;
            sym = toUpper(sym);
            input >> d;

            if (!isItANumber(d)) {
                q = atoi(d.c_str());
                input >> d;
                if (isItANumber(d)) {
                    cout << "\n\tCannot process transaction" << endl;
                    continue;
                }
                else {
                    price = atof(d.c_str());
                }
            }
            else {
                cout << "\n\tCannot process transaction" << endl;
                continue;
            }

            if (account.buyStock(sym, price, q)) {
                now = time(0);
                t1 = localtime(&now);
                stockTransaction.clear();
                stockTransaction.seekp(0, ios::end);
                stockTransaction << "\tBuy" << "\t\t" << sym << "\t\t" << q << "\t\t$" << price << "\t\t";
                stockTransaction << t1->tm_hour << ":" << t1->tm_min << ":" << t1->tm_sec << endl;
            }
        }

        else if (c == 3) {
            cout << "\n\tEnter sell options: ";
            input >> sym;
            sym = toUpper(sym);

            input >> d;
            if (!isItANumber(d)) {
                q = atoi(d.c_str());
                input >> d;
                if (isItANumber(d)) {
                    cout << "\n\tCannot process transaction" << endl;
                    continue;
                }
                else {
                    price = atof(d.c_str());
                }
            }
            else {
                cout << "\n\tCannot process transaction!" << endl;
                continue;
            }

            if (account.sellStock(sym, price, q)) {
                now = time(0);
                t1 = localtime(&now);
                stockTransaction.clear();
                stockTransaction.seekp(0, ios::end);
                stockTransaction << "\tSell" << "\t\t" << sym << "\t\t" << q << "\t\t$" << price << "\t\t";
                stockTransaction << t1->tm_hour << ":" << t1->tm_min << ":" << t1->tm_sec << endl;

            }
        }

        else if (c == 4) {
            account.displayPortfolio();
        }

        else if (c == 5) {
            displayTransactionHistory(stockTransaction);
        }

        else if (c == 6) {
            return;
        }
        else {
            cout << "\t Invalid choice!\n";
        }

    }

}

//this menu shows up when the user calls the bank menu
void bankMenu(StockAccount &account, istream &input, fstream &bankTransaction) {
    int c;//c is the choice you decided
    double amount;
    string d;//d is the input that you entered
    time_t now;
    tm* t1;

    while (true) {
        cout << "\n\t 1. View account balance" << endl;
        cout << "\t 2. Deposit money" << endl;
        cout << "\t 3. Withdraw money" << endl;
        cout << "\t 4. Display transactions history" << endl;
        cout << "\t 5. Return to previous menu" << endl;
        cout << "\t Your selection: ";
        input >> d;
        if (isItANumber(d)) {
            cout << "\tInvalid input!" << endl;
            continue;
        }
        else
            c = atoi(d.c_str());

        if (c == 1) {
            account.displayPortfolio();
        }
        else if (c == 2) {
            cout << "\n\tEnter amount to deposit: ";
            do {
                input >> d;
                if (isItANumber(d)) {
                    cout << "\tInvalid input!" << endl;
                    continue;
                }
                else
                    amount = atof(d.c_str());

                if (amount <= 0)
                    cout << "\n\t Enter a positive value for amount!" << endl;
                else
                    break;
            } while (true);


            account.deposit(amount);
            cout << "\n\tDeposit $" << amount << " to bank account" << endl;

            account.displayPortfolio();
            bankTransaction << "\tDeposit" << "\t\t$" << amount << "\t\t$" << account.getBankAccount().getBalance() << "\t\t\t";
            now = time(0);
            t1 = localtime(&now);
            //This will read the current time and date base on the clock found in the computer
            bankTransaction << t1->tm_mday << "/" << t1->tm_mon << "/" << (1900 + t1->tm_year) << "\t\t";
            bankTransaction << t1->tm_hour << ":" << t1->tm_min << ":" << t1->tm_sec << endl;

        }
        else if (c == 3) {
            cout << "\n\tEnter amount to withdraw: ";
            do {
                input >> d;
                if (isItANumber(d)) {
                    cout << "\tInvalid input!" << endl;
                    continue;
                }
                else
                    amount = atof(d.c_str());

                if (amount <= 0)
                    cout << "\n\t Enter a positive value for amount! ";
                else
                    break;
            } while (true);

            if (account.withdraw(amount)) {
                cout << "\n\tWithdraw $" << amount << " from bank account" << endl;

                account.displayPortfolio();
                bankTransaction << "\tWithdraw" << "\t$" << amount << "\t\t$" << account.getBankAccount().getBalance() << "\t\t";
                now = time(0);
                t1 = localtime(&now);
                bankTransaction << t1->tm_mday << "/" << t1->tm_mon << "/" << (1900 + t1->tm_year) << "\t\t";
                bankTransaction << t1->tm_hour << ":" << t1->tm_min << ":" << t1->tm_sec << endl;
            }
            else {
                cout << "\n\t Invalid input!\n";
            }
        }

        else if (c == 4) {
            displayTransactionHistory(bankTransaction);
        }

        else if (c == 5) {
            return;
        }
        else {
            cout << "\t Invalid choice!\n";
        }
    }
}

//This is the main menu of the code
void mainMenu(StockAccount &account, istream &input) {
    fstream bankTransaction("bank_transaction_history.txt", ios::in | ios::out | ios::trunc);
    fstream stockTransaction("stocks_transaction_history.txt", ios::in | ios::out | ios::trunc);
    if (!bankTransaction.is_open() || !stockTransaction.is_open()) {
        cout << "\n\tError creating transaction files." << endl;
        exit(1);
    }

    stockTransaction << "\tAction\t\tSymbol\t\tShares\t\tPrice\t\tTime\n";
    bankTransaction << "\tAction\t\tAmount\t\tCash Balance\t\tDate\t\t\tTime\n";

    cout << "\nWelcome to the Accounts Management System.";

    string d;//d is the input that you entered
    int c;//c is the choice you decided and q is the quality

    while (true) {
        cout << "\n\tPlease select an account to access" << endl;
        cout << "\t1. Stock Portfolio Accounts" << endl;
        cout << "\t2. Bank Accounts" << endl;
        cout << "\t3. Exit" << endl;
        cout << "\tYour selection: ";
        input >> d;
        if (isItANumber(d)) {
            cout << "\n\t Invalid input!";
            continue;
        }
        else
            c = atoi(d.c_str());

        if (c == 1)
            stockMenu(account, input, stockTransaction);

        else if (c == 2)
            bankMenu(account, input, bankTransaction);

        else if (c == 3) {
            stockTransaction.close();
            bankTransaction.close();
            account.closeFiles();
            break;
        }
        else
            cout << "\n\tInvalid choice!" << endl;;
    }
}


int main(int argc, char *argv[]) {
    //stocks vector is found in the Stocks.h file and defined in Stocks.cpp
    string files[] = {"stock1.txt","stock2.txt","stock3.txt","stock4.txt"};
    //The text files are put into the cmake-build-debug folder

    StockAccount account(10000, files, 4);
    if (argc<2)
        mainMenu(account, cin);
    else {
        ifstream input(argv[1]);
        if (argc>1 && !input.is_open()) {
            cout << "Error opening file : " << argv[1] << endl;
            //this only shows up if the stock(#1-4) cannot be found
            return -1;
        }
        mainMenu(account, input);
    }
    cout << "\n\tProgram terminated." << endl;
    return 0;
}