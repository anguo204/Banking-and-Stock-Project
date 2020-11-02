#include "Stocks.h"

Stock::Stock(string sym, int qty) {
    symbol = sym;
    quantity = qty;
}
int Stock::getQuantity() {
    return quantity;
}
void Stock::setQuantity(int qty) {
    quantity = qty;
}
std::string Stock::getSymbol() {
    return symbol;
}
void Stock::setSymbol(std::string sym) {
    symbol = sym;
}
