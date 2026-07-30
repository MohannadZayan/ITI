#include "../include/SavingsAccount.h"
#include <iostream>
#include <stdexcept>
#include <iomanip> //for setprecision

using namespace std;

SavingsAccount::SavingsAccount (string id, string owner, double initialBalance) 
: Account(id, owner, initialBalance) 
{
    
}

void SavingsAccount::withdraw (double amount) {          //savings accounts are NOT allowed to go below zero

    if (amount <= 0) {
        throw invalid_argument ("Withdrawal amount must be greater than zero.");
    }

    if (balance < amount) {
        throw runtime_error ("Insufficient funds in account.");   //Runtime error because the input was valid but the operation failed 
    }

    balance -= amount;

    cout << "Successfully withdrew " << amount << " from account " << accountID << endl;
}

void SavingsAccount::display() const {

    cout << fixed << setprecision(2);
    
    cout << "========== Savings Account ==========" << endl;
    cout << "Account ID: " << accountID << endl;
    cout << "Owner: " << ownerName << endl;
    cout << "Balance: " << balance << endl;
    cout << "====================================" << endl;
}

string SavingsAccount::getType() const {
    return "Savings Account";
}

string SavingsAccount::serialize() const {
    return getType () + "," +
           accountID + "," +
           ownerName + "," +
           to_string(balance);
}
