#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// An interface for every library item that can be borrowed.
class borrowable {
public:
    virtual bool borrowBook() = 0;
    virtual bool returnBook() = 0;
    virtual bool checkAvailability() const = 0;
    virtual ~borrowable() {}
};

class Book : public borrowable {
private:
    string title;
    string author;
    int bookId;
    bool isAvailable;
    static int nextBookId;

public:
    Book(const string& title, const string& author)
        : title(title), author(author), bookId(0), isAvailable(true) {}

    // The Library calls this only when it adds the book.
    void assignBookId() {
        bookId = ++nextBookId;
    }

    int getBookId() const {
        return bookId;
    }

    void displayBookInfo() const {
        cout << "Book ID: " << bookId
             << " | Title: " << title
             << " | Author: " << author
             << " | " << (isAvailable ? "Available" : "Borrowed") << '\n';
    }

    bool borrowBook() override {
        if (!isAvailable) {
            return false;
        }

        isAvailable = false;
        return true;
    }

    bool returnBook() override {
        if (isAvailable) {
            return false;
        }

        isAvailable = true;
        return true;
    }

    bool checkAvailability() const override {
        return isAvailable;
    }
};

int Book::nextBookId = 0;

class User {
protected:
    string name;
    int id;

public:
    User(const string& name, int id) : name(name), id(id) {}
    virtual void displayInfo() const = 0;
    virtual ~User() {}
};

class Student : public User {
public:
    Student(const string& name, int id) : User(name, id) {}

    void displayInfo() const override {
        cout << "Student ID: " << id << " | Name: " << name << '\n';
    }
};

class Teacher : public User {
public:
    Teacher(const string& name, int id) : User(name, id) {}

    void displayInfo() const override {
        cout << "Teacher ID: " << id << " | Name: " << name << '\n';
    }
};

class Library {
private:
    vector<Book> books;
    vector<User*> users;

public:
    ~Library() {
        for (User* user : users) {
            delete user;
        }
    }

    void addBook(const string& title, const string& author) {
        Book book(title, author);
        book.assignBookId();
        books.push_back(book);
    }

    // The Library owns users added with this function.
    void addUser(User* user) {
        if (user != nullptr) {
            users.push_back(user);
        }
    }

    void displayBooks() const {
        cout << "\n--- Books ---\n";
        if (books.empty()) {
            cout << "No books found.\n";
        }

        for (const Book& book : books) {
            book.displayBookInfo();
        }
    }

    void displayUsers() const {
        cout << "\n--- Users ---\n";
        if (users.empty()) {
            cout << "No users found.\n";
        }

        for (const User* user : users) {
            user->displayInfo();
        }
    }

    bool borrowBook(int id) {
        vector<Book>::iterator book = find_if(
            books.begin(), books.end(),
            [id](const Book& currentBook) { return currentBook.getBookId() == id; });

        return book != books.end() && book->borrowBook();
    }

    bool returnBook(int id) {
        vector<Book>::iterator book = find_if(
            books.begin(), books.end(),
            [id](const Book& currentBook) { return currentBook.getBookId() == id; });

        return book != books.end() && book->returnBook();
    }
};

int main() {
    Library library;
    int choice = 0;

    do {
        cout << "\n===== Library Management System =====\n"
             << "1. Add book\n"
             << "2. Add student\n"
             << "3. Add teacher\n"
             << "4. Display books\n"
             << "5. Display users\n"
             << "6. Borrow book\n"
             << "7. Return book\n"
             << "0. Exit\n"
             << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title;
                string author;

                cout << "Book title: ";
                cin >> ws;
                getline(cin, title);
                cout << "Book author: ";
                getline(cin, author);
                library.addBook(title, author);
                cout << "Book added successfully.\n";
                break;
            }

            case 2: {
                string name;
                int id;

                cout << "Student name: ";
                cin >> ws;
                getline(cin, name);
                cout << "Student ID: ";
                cin >> id;
                library.addUser(new Student(name, id));
                cout << "Student added successfully.\n";
                break;
            }

            case 3: {
                string name;
                int id;

                cout << "Teacher name: ";
                cin >> ws;
                getline(cin, name);
                cout << "Teacher ID: ";
                cin >> id;
                library.addUser(new Teacher(name, id));
                cout << "Teacher added successfully.\n";
                break;
            }

            case 4:
                library.displayBooks();
                break;

            case 5:
                library.displayUsers();
                break;

            case 6: {
                int bookId;
                cout << "Book ID: ";
                cin >> bookId;

                if (library.borrowBook(bookId)) {
                    cout << "Book borrowed successfully.\n";
                } else {
                    cout << "Operation failed. Check the book ID and its current status.\n";
                }
                break;
            }

            case 7: {
                int bookId;
                cout << "Book ID: ";
                cin >> bookId;

                if (library.returnBook(bookId)) {
                    cout << "Book returned successfully.\n";
                } else {
                    cout << "Operation failed. Check the book ID and its current status.\n";
                }
                break;
            }

            case 0:
                break;

            default:
                cout << "Invalid option. Please try again.\n";
        }
    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}
