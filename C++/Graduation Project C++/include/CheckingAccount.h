#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H
#include "Account.h"

 class CheckingAccount : public Account {

    private:
    double overdraftLimit;


    public :

    CheckingAccount (string id, string owner, double initialBalance, double overdraft);

    void withdraw (double amount) override;
    void display() const override;
    string getType() const override;
    string serialize() const override;

};

#endif