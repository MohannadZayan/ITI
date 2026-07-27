#include<iostream>
using namespace std;

double Add(double a, double b) {
    return a + b;
}

double Subtract(double a, double b) {
    return a - b;
}

double Multiply(double a, double b) {
    return a * b;
}

double Divide(double a, double b) {
    if (b == 0) {
        throw invalid_argument("Division by zero is not allowed.");
    }
    return a / b;
}

int main () {
    cout << "Enter two numbers and the operation, for example 3 + 4: ";
    double num1, num2;
    char operation;
    cin >> num1 >> operation >> num2;
    switch (operation) {
        case '+':
            cout << "Result: " << Add(num1, num2) << endl;
            break;
        case '-':
            cout << "Result: " << Subtract(num1, num2) << endl;
            break;
        case '*':
            cout << "Result: " << Multiply(num1, num2) << endl;
            break;
        case '/':
            try {
                cout << "Result: " << Divide(num1, num2) << endl;
            } catch (const invalid_argument& e) {
                cout << e.what() << endl;
            }
            break;
        default:
            cout << "Invalid operation." << endl;
    }
    return 0;
}