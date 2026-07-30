#include "../include/Account.h"
#include <iostream>

int Account::accountCount = 0;

Account::Account(string id, string owner, double initialBalance) 
:  accountID(id), ownerName(owner), balance(initialBalance)          //INITIALIZER LIST
{
    accountCount++;
}

Account::~Account()
{
    accountCount--;
}

string Account::getAccountID() const
{
    return accountID;
}

string Account::getOwnerName() const
{
    return ownerName;
}

double Account::getBalance() const
{
    return balance;
}

int Account::getAccountCount()
{
    return accountCount;
}

void Account::deposit(double amount)
{
    if (amount <= 0) {
        throw invalid_argument ("Deposit amount must be greater than zero.");
    }
    balance += amount;

    cout << "Successfully deposited " << amount << " into account " << accountID << endl;
}