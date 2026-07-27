#include <iostream>
#include "bank.h"

using namespace std;

void CheckBalance(double balance) {
    cout << "Your current balance is: $" << balance << endl;
}

void Deposit(double &balance) {
    double amount;
    cout << "Enter the amount to deposit: $";
    cin >> amount;
    if (amount > 0) {
        balance += amount;
        cout << "Successfully deposited $" << amount << ". New balance: $" << balance << endl;
    } else {
        cout << "Invalid deposit amount." << endl;
    }
}

void Withdraw(double &balance) {
    double amount;
    cout << "Enter the amount to withdraw: $";
    cin >> amount;
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        cout << "Successfully withdrew $" << amount << ". New balance: $" << balance << endl;
    } else {
        cout << "Invalid withdrawal amount." << endl;
    }
}