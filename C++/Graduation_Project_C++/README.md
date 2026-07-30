#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>

using namespace std;

class Account {
    protected: 
    string AccountID;
    string OwnerName;
    double Balance;

    static int AccountCount;

    public:
    Account (string id, string owner, double InitialBalance);
    virtual ~Account();

    string getAccountID() const;
    string getOwnerName() const;
    double getBalance() const;

    static int getAccountCount();

    virtual void depost(double amount);
    virtual void withdraw(double amount);

    virtual void display() const = 0;
    virtual string getType() const = 0;
    virtual string serialize () const = 0;
};


























#endif