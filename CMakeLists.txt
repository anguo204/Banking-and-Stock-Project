cmake_minimum_required(VERSION 3.9)
project(project2)

set(CMAKE_CXX_STANDARD 11)

add_executable(project2 main.cpp Accounts.h Accounts.cpp Stocks.cpp Stocks.h BankAccounts.h BankAccounts.cpp StocksAccount.h StocksAccount.cpp)