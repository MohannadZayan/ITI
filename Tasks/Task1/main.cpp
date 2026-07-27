#include <iostream>
#include "menu.h"
#include "bank.h"

using namespace std;

int main() {

    double balance = 1000.0;
    int choice;

    do {
        cout << endl;
        showMenu();
        
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number between 1 and 4: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        if (choice < 1 || choice > 4) {
            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
            continue;
        }

        switch (choice) {
            case 1:
                CheckBalance(balance);
                break;
            case 2:
                Deposit(balance);
                break;
            case 3:
                Withdraw(balance);
                break;
            case 4:
                cout << "Thank you for using the Bank Management System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}