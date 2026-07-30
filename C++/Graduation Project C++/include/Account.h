#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

using namespace std;

class Account
{
protected:
    string accountID;
    string ownerName;
    double balance;

    static int accountCount;

public:
    // Constructor
    Account(string id, string owner, double initialBalance);

    // Virtual destructor
    virtual ~Account();

    // Getters
    string getAccountID() const;
    string getOwnerName() const;
    double getBalance() const;

    // Static getter
    static int getAccountCount();

    // Banking operations
    virtual void deposit(double amount);
    virtual void withdraw(double amount);

    // Pure virtual functions
    virtual void display() const = 0;
    virtual string getType() const = 0;
    virtual string serialize() const = 0;
};

#endif