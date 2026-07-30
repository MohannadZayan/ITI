#include <../include/CheckingAccount.h>
#include <iostream>
#include <stdexcept>
#include <iomanip> //for setprecision

using namespace std;

CheckingAccount::CheckingAccount (string id, string owner, double initialBalance, double overdraft)
: Account(id, owner, initialBalance), overdraftLimit(overdraft)
 { }

 void CheckingAccount::withdraw (double amount) {   //checking accounts are allowed to go below zero  
         if (amount <= 0) {
             throw invalid_argument ("Withdrawal amount must be greater than zero.");
         }

         if (balance -amount <overdraftLimit) {
             throw runtime_error ("Exceeded overdraft limit.");
         }

         balance -= amount;

         cout << "Successfully withdrew " << amount << " from account " << accountID << endl;
 }

 void CheckingAccount::display() const {

     cout << fixed << setprecision(2);

     cout << "========== Checking Account ==========" << endl;
     cout << "Account ID: " << accountID << endl;
     cout << "Owner: " << ownerName << endl;
     cout << "Balance: " << balance << endl;
     cout << "Overdraft Limit: " << overdraftLimit << endl;
     cout << "====================================" << endl;
 }

 string CheckingAccount::getType() const {
     return "Checking Account";
 }

 string CheckingAccount::serialize() const {
     return getType () + "," +
            accountID + "," +
            ownerName + "," +
            to_string(balance) + "," +
            to_string(overdraftLimit);
 }