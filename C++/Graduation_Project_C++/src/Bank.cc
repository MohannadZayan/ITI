#include "../include/Bank.h"
#include "../include/CheckingAccount.h"
#include "../include/SavingsAccount.h"


#include <iostream>
#include <fstream> //FOR FILE HANDLING
#include <sstream> // FOR FILE HANDLINE
#include <stdexcept>
#include <algorithm>

using namespace std;

Bank::Bank () 
{

}

shared_ptr<Account> Bank:: findAccount (const string &id) const  {
    for (const auto &account : accounts) {
        if (account->getAccountID() == id) {
            return account;
        }
    }
    return nullptr;
}

bool Bank :: accountExists (const string &id) const {
    return findAccount (id) != nullptr;
}

//=====CREATE ACCOUNT=====

void Bank :: createAccount (const string &id, const string &owner, double initialBalance, const string &type, double overdraftLimit) {

    if (accountExists (id)) {
        throw runtime_error ("Account with id " + id + " already exists.");
    }

    if (type == "Savings") {
        accounts.push_back (make_shared<SavingsAccount> (id, owner, initialBalance));       //this is valid because a savings account IS an account
        saveAccounts();
}

else if (type == "Checking") {
    accounts.push_back (make_shared<CheckingAccount> (id, owner, initialBalance, overdraftLimit)); //same here
    saveAccounts();
}
else {
    throw invalid_argument ("Invalid account type.");
}

if (type == "Checking")
logTransactions ( "CREATE | " + id + " | " + owner + " | " + to_string(initialBalance) + " | " + type + " | " + to_string(overdraftLimit));

if (type == "Savings")
logTransactions ( "CREATE | " + id + " | " + owner + " | " + to_string(initialBalance) + " | " + type);

cout << "Successfully created account with id: " << id << endl;
}



//=====DELETE ACCOUNT=====
void Bank :: deleteAccount (const string &id) {
    auto account = findAccount (id);

    if (account == nullptr) {
        throw invalid_argument ("Account with id " + id + " does not exist.");
    }

    auto it = find (accounts.begin(), accounts.end(), account); //find returns an iterator to the element to be deleted
    logTransactions ( "DELETE | " + id);
    accounts.erase (it);

    cout << "Successfully deleted account with id: " << id << endl;
}


//=====DEPOSIT=====
void Bank :: deposit (const string &id, double amount) {
    auto account = findAccount (id);

    if (account == nullptr) {
        throw invalid_argument ("Account with id " + id + " does not exist.");
    }

    account->deposit (amount);
    logTransactions ( "DEPOSIT | " + id + " | " + to_string(amount));
}



//=====WITHDRAW=====
void Bank :: withdraw (const string &id, double amount) {
    auto account = findAccount (id);

    if (account == nullptr) {
        throw invalid_argument ("Account with id " + id + " does not exist.");
    }

    account->withdraw (amount);
    logTransactions ( "WITHDRAW | " + id + " | " + to_string(amount));
}


//=====TRANSFER MONEY=====
void Bank :: transferMoney (const string &fromID, const string &toID, double amount) {
    if (fromID == toID) {
        throw invalid_argument("Cannot transfer money to the same account.");
    }

    auto fromAccount = findAccount(fromID);
    auto toAccount = findAccount(toID);

    if (fromAccount == nullptr || toAccount == nullptr) {
        throw invalid_argument("One or both accounts do not exist.");
    }

    if (amount > fromAccount->getBalance()) {
        throw runtime_error("Insufficient funds in account.");
    }

    fromAccount->withdraw(amount);
    toAccount->deposit(amount);
    logTransactions("TRANSFER | " + fromID + " | " + toID + " | " + to_string(amount));
}



//=====DISPLAY ALL ACCOUNTS=====
void Bank :: displayAllAccounts() const {

    if (accounts.empty()) {
        cout << "There are no accounts in the bank." << endl;
        return;
    }

    for (const auto &account : accounts) {
        account->display();
        cout << endl;
    }

    cout  << "Total number of accounts: " << Account::getAccountCount() << endl;
}

//=====DISPLAY ONE ACCOUNT=====

void Bank :: displayAccount (const string &id) const {
    auto account = findAccount (id);

    if (account == nullptr) {
        throw invalid_argument ("Account with id " + id + " does not exist.");
    }

    account->display();
}

//FILE HANDLING:
void Bank :: saveAccounts() const {
    ofstream file ("data/accounts.txt", ios::app);     //opens the file

    if (!file) {         //check if the file was opened successfully
        throw runtime_error ("Failed to open accounts.txt for writing.");
    }

    for (const auto &account : accounts) {
        file << account-> serialize() << endl;        //serialize turns an object into a string
    }
    file.close();
    cout << "Successfully saved accounts to accounts.txt." << endl;
}

void Bank::loadAccounts()
{
    ifstream file("data/accounts.txt");

    if (!file)
    {
        throw runtime_error("Failed to open accounts.txt for reading.");
    }

    accounts.clear();

    string line;

    // Read the file one line at a time and load one account per iteration.
    while (getline(file, line))
    {
        stringstream ss(line);
        string type;
        string id;
        string owner;
        double balance;

        getline(ss, type, ',');
        getline(ss, id, ',');
        getline(ss, owner, ',');
        ss >> balance;

        if (type == "Savings")
        {
            accounts.push_back(make_shared<SavingsAccount>(id, owner, balance));
        }
        else if (type == "Checking")
        {
            double overdraftLimit;
            ss.ignore();
            ss >> overdraftLimit;

            accounts.push_back(make_shared<CheckingAccount>(id, owner, balance, overdraftLimit));
        }
        else
        {
            throw runtime_error("Invalid account type found in accounts.txt.");
        }
    }

    file.close();

    cout << "Successfully loaded accounts from accounts.txt." << endl;
}

void Bank :: logTransactions (const string & transaction) const {

    ofstream file ("data/transactions.txt", ios::app);     //opens the file, ios :: app appends to the end of the file instead of overwriting it

    if (!file) {         //check if the file was opened successfully
        throw runtime_error ("Failed to open transactions.txt");
    }

    file << transaction << endl;

    file.close();
    cout << "Successfully logged transaction to transactions.txt." << endl;
    
}
