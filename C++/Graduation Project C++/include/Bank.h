#ifndef BANK_H
#define BANK_H

#include <vector>
#include <string>
#include <memory>

#include "Account.h"

using namespace std;

class Bank {

    private :
    vector <shared_ptr<Account>> accounts; //vector of smart pointers to accounts

    void logTransactions (const string & transaction) const;

    public : 

    Bank ();      //Constructor

    //ACCOUNT MANAGEMENT:

    void createAccount (const string &id, const string &owner, double initialBalance, const string &type, double overdraftLimit = 0);        //Here, the overdraft limit is set to 0 by default to see if it's a checking or savings account

    void deleteAccount (const string &id);

    //ACCOUNT SEARCHING:

    shared_ptr<Account> findAccount (const string &id) const;
    bool accountExists (const string &id) const;

    //BANK OPERATIONS:

    void deposit (const string &id, double amount);
    void withdraw (const string &id, double amount);

    //BANK INFORMATION:
    void displayAllAccounts() const;
    void displayAccount (const string &id) const;

    //FILE HANDLING:

    void saveAccounts() const;
    void loadAccounts();

};

#endif