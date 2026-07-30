#include "../include/Bank.h"

#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

int main()
{
    Bank bank;

    // Try loading previously saved accounts
    try
    {
        bank.loadAccounts();
    }
    catch (const exception &e)
    {
        cout << "Failed to load accounts: " << e.what() << endl;
        cout << "Starting with an empty bank." << endl;
    }

    auto clearInput = []()          //helper lambda 3shan a3saby 
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    };

    int choice;

    while (true)
    {
        cout << "\n=====================================\n";
        cout << "     BANK MANAGEMENT SYSTEM\n";
        cout << "=====================================\n";
        cout << "1. Create Account\n";
        cout << "2. Delete Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Display All Accounts\n";
        cout << "6. Search Account\n";
        cout << "9. Exit\n";
        cout << "=====================================\n";

        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a valid number." << endl;
            clearInput();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        try
        {
            switch (choice)
            {
case 1:
{
    string id;
    string owner;
    string type;
    double balance;
    double overdraft = 0;

    cout << "Enter Account ID: ";
    getline(cin, id);

    while (id.empty())
    {
        cout << "ID cannot be empty. Try again: ";
        getline(cin, id);
    }

    cout << "Enter Owner Name: ";
    getline(cin, owner);

    while (owner.empty())
    {
        cout << "Owner name cannot be empty. Try again: ";
        getline(cin, owner);
    }

    cout << "Enter Initial Balance: ";

    while (!(cin >> balance) || balance < 0)
    {
        cout << "Invalid balance. Try again: ";
        clearInput();
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Account Type (Savings/Checking): ";
    getline(cin, type);

    while (type != "Savings" && type != "Checking")
    {
        cout << "Invalid account type. Enter Savings or Checking: ";
        getline(cin, type);
    }

    if (type == "Checking")
    {
        cout << "Enter Overdraft Limit: ";

        while (!(cin >> overdraft) || overdraft < 0)
        {
            cout << "Invalid overdraft limit. Try again: ";
            clearInput();
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    bank.createAccount(id, owner, type, balance, overdraft);

    break;
}



case 2:
{
    string id;

    cout << "Enter Account ID: ";
    getline(cin, id);

    while (id.empty())
    {
        cout << "ID cannot be empty. Try again: ";
        getline(cin, id);
    }

    bank.deleteAccount(id);

    break;
}



case 3:
{
    string id;
    double amount;

    cout << "Enter Account ID: ";
    getline(cin, id);

    while (id.empty())
    {
        cout << "ID cannot be empty. Try again: ";
        getline(cin, id);
    }

    cout << "Enter Deposit Amount: ";

    while (!(cin >> amount) || amount <= 0)
    {
        cout << "Invalid amount. Try again: ";
        clearInput();
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bank.deposit(id, amount);

    break;
}

case 4:
{
    string id;
    double amount;

    cout << "Enter Account ID: ";
    getline(cin, id);

    while (id.empty())
    {
        cout << "ID cannot be empty. Try again: ";
        getline(cin, id);
    }

    cout << "Enter Withdrawal Amount: ";

    while (!(cin >> amount) || amount <= 0)
    {
        cout << "Invalid amount. Try again: ";
        clearInput();
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bank.withdraw(id, amount);

    break;
}

case 5:
{
    bank.displayAllAccounts();

    break;
}

case 6:
{
    string id;

    cout << "Enter Account ID: ";
    getline(cin, id);

    while (id.empty())
    {
        cout << "ID cannot be empty. Try again: ";
        getline(cin, id);
    }

    bank.displayAccount(id);

    break;
}

case 9:
{
    bank.saveAccounts();

    cout << "Thank you for using the Bank Management System By Mohannad Zayan!" << endl;

    return 0;
}
            default:
                cout << "Invalid menu choice." << endl;
                break;
            }
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }
}