#include <iostream>
#include <string>
using namespace std;

class Employee {
protected:
    string name;

public:
    Employee(string name) {
        this->name = name;
        cout << "Employee Constructor\n";
    }

    virtual void work() const {
        cout << name << " is working\n";
    }

    virtual ~Employee() {
        cout << "Employee Destructor\n";
    }
};


class Developer : public Employee {
public:
    Developer(string name) : Employee(name) {
        cout << "Developer Constructor\n";
    }

    void work() const override {
        cout << name << " is developing software\n";
    }

    ~Developer() {
        cout << "Developer Destructor\n";
    }
};


class Tester : public Employee {
public:
    Tester(string name) : Employee(name) {
        cout << "Tester Constructor\n";
    }

    void work() const override {
        cout << name << " is testing software\n";
    }

    ~Tester() {
        cout << "Tester Destructor\n";
    }
};


int main() {
    Developer d1("Mohannad");
    Tester t1("Ahmed");

    d1.work();
    t1.work();

    return 0;
}