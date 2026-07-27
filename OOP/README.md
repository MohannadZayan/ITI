# Library Management System

A small C++ console project for practicing classes, inheritance, abstract classes, vectors, and basic user input.

The program lets a librarian add books and users, then borrow or return books by their ID. It is intentionally simple and keeps all data only while the program is running.

## What it can do

- Add books with a title and author
- Give each added book a unique ID automatically
- Add students and teachers as library users
- Display all books and users
- Borrow an available book
- Return a borrowed book

## Class structure

- `borrowable` is an abstract interface for objects that can be borrowed.
- `Book` implements `borrowable` and keeps its title, author, ID, and availability status.
- `User` is an abstract base class.
- `Student` and `Teacher` inherit from `User` and provide their own `displayInfo()` implementation.
- `Library` stores `vector<Book>` and `vector<User*>`, and handles the menu operations.

## Build and run

From the project root, compile the program with:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic OOP/Library.cc -o library
```

Then run it:

```bash
./library
```

## Menu

When the program starts, choose one of these options:

```text
1. Add book
2. Add student
3. Add teacher
4. Display books
5. Display users
6. Borrow book
7. Return book
0. Exit
```

For borrowing and returning, use the book ID shown when you display the book list. A book cannot be borrowed twice until it has been returned.

## Notes

This project uses only `iostream`, `vector`, `algorithm`, and `string`. It is meant as a learning exercise, so it does not save books or users to a file after the program exits.
