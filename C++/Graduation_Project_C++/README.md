# Bank Management System

This project is a small C++ banking system that helps the user manage bank accounts. It allows creating accounts, deleting them, depositing money, withdrawing money, displaying account details, and saving data to files.

The main purpose of this project is to practice object-oriented programming, especially inheritance, polymorphism, and file handling.

## Project idea

The system is based on the idea that different account types share the same basic structure. Every account has an ID, an owner name, and a balance. The difference is in how each account type behaves during withdrawal.

- A savings account does not allow the balance to go below zero.
- A checking account allows a limited overdraft.

This is a good example of using inheritance and virtual functions in C++.

## Classes in the project

### 1. Account
This is the base class for all accounts.

It stores the common information for every account:
- account ID
- owner name
- balance

It also contains the common operations:
- deposit money
- get account information

The class is abstract, so it cannot be used directly to create objects. It defines the basic structure that the other account classes must follow.

### 2. SavingsAccount
This class represents a savings account.

It inherits from Account and uses the same basic data, but it has its own withdrawal rules. A savings account cannot allow the balance to become negative.

So if the user tries to withdraw more money than the account has, the program shows an error.

### 3. CheckingAccount
This class represents a checking account.

It also inherits from Account, but it has an extra feature: an overdraft limit. That means the account can go below zero, but only up to a certain limit.

This makes the withdrawal rule different from a savings account.

### 4. Bank
This is the most important class in the project.

The Bank class is responsible for managing all accounts. It keeps a list of accounts and provides the main operations of the system. In this project, the bank uses smart pointers, which makes memory management safer.

The Bank class does not work with only one account type. It stores accounts through the base class, which allows it to handle both savings and checking accounts in the same way.

## What the Bank class does

The Bank class is the heart of the project because it connects everything together.

### createAccount
This function creates a new account.

It checks whether the account ID already exists, then creates either a SavingsAccount or a CheckingAccount depending on the type chosen by the user. If the account type is invalid, it throws an error.

### deleteAccount
This function removes an account from the bank using its ID.

Before deleting it, the program checks whether the account really exists.

### deposit
This function adds money to an existing account.

It first finds the account by ID, then calls the deposit function of that account.

### withdraw
This function removes money from an existing account.

It finds the account first, then calls the correct withdraw logic based on the account type. This is where polymorphism is useful, because the same method name works differently depending on the object.

### displayAllAccounts and displayAccount
These functions show account information to the user.

They are used to view the details of one account or all accounts in the bank.

### saveAccounts and loadAccounts
These functions read and write account data to files.

The project uses text files to keep the data saved between program runs. This is an important part of the system because the bank should not lose all its data every time the program closes.

### logTransactions
This function records every important action in a transaction file.

For example, when an account is created, deleted, deposited into, or withdrawn from, the action is logged in the transactions file.

## Why Bank.cc is the most complicated part

The file Bank.cc is the most complicated because it contains most of the system logic.

It is responsible for:
- managing the list of accounts
- finding accounts by ID
- creating and removing accounts
- handling deposits and withdrawals
- saving and loading data from files
- logging transactions

This file brings many different tasks together, so it is the main place where the whole project comes together.

## Main program

The main function provides the menu for the user.

It lets the user choose actions such as:
- create an account
- delete an account
- deposit money
- withdraw money
- display accounts
- exit the program

The program keeps running until the user decides to leave.

## File structure

- include/: contains the class declarations
- src/: contains the class implementations
- data/accounts.txt: stores account data
- data/transactions.txt: stores transaction history

## Summary

This project is a simple but useful example of how a banking system can be built in C++. It shows how classes can work together, how inheritance can reduce repeated code, and how object-oriented programming makes complex systems easier to organize.
