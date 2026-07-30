#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
    public : SavingsAccount(string id, string owner, double initialBalance);

    void withddraw (double amount) override;
    void display() const override;
    string getType() const override;
    string serialize() const override;
     
};

#endif