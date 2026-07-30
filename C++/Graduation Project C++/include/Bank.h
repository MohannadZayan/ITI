#ifndef BANK_H
#define BANK_H

#include <vector>
#include <string>
#include <memory>

#include "Account.h"
#include "CheckingAccount.h"
#include "SavingsAccount.h"

using namespace std;

class Bank {

    private :
    vector <shared_ptr<Account>> accounts; //vector of smart pointers to accounts

    public : 

    Bank ();      //Constructor

    //ACCOUNT MANAGEMENT:

    void createAccount (string id, string owner, double initialBalance, string type, double overdraftLimit = 0);        //Here, the overdraft limit is set to 0 by default to see if it's a checking or savings account

    void deleteAccount (string id);

    //ACCOUNT SEARCHING:

    shared_ptr<Account> findAccount (string id);
    bool accountExists (string id) const;

    //BANK OPERATIONS:

    void deposit (string id, double amount);
    void withdraw (string id, double amount);

    //BANK INFORMATION:
    void displayAllAccounts() const;

    //FILE HANDLINE:

    void saveAccounts() const;
    void loadAccounts();

};

#endif