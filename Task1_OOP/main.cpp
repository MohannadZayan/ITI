#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Student {
    private :
    int id;
    string name;
    int age;
    string major;
    double gpa;

    public :
    Student (int studentID, string studentName, int studentAge, string studentMajor, double studentGpa) {
        id = studentID;
        name = studentName;
        age = studentAge;
        major = studentMajor;
        gpa = studentGpa;
    }

    int getID () {
        return id;
    }

    string getName () {
        return name;
    }

    int getAge () {
        return age;
    }
    string getMajor () {
        return major;
    }
    double getGpa () {
        return gpa;
    }

 void setId(int studentId)
    {
        id = studentId;
    }

    void setName(string studentName)
    {
        name = studentName;
    }

    void setAge(int studentAge)
    {
        age = studentAge;
    }

    void setMajor(string studentMajor)
    {
        major = studentMajor;
    }

    void setGpa(double studentGpa)
    {
        gpa = studentGpa;
    }

    void displayInfo() {
        cout<< "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Major: " << major << endl;
        cout << "GPA: " << gpa << endl;
    } 
};

int main () {
    vector <Student> students;
    int choice;
    do {
        cout << "\n==========STUDENT MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Student\n";
        cout << "2. View All students\n";
        cout << "3. Search for a student\n";
        cout << "4. Exit\n";

        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            int age;
            string major;
            double gpa;

            cout << "\nEnter Student ID: ";
            cin >> id;

            cout << "Enter Student Name: ";
            getline(cin, name);

            cout << "Enter Student Age: ";
            cin >> age;


            cout << "Enter Student Major: ";
            getline(cin, major);

            cout << "Enter Student GPA: ";
            cin >> gpa;

            Student newStudent (id,name,age,major,gpa);

            students.push_back (newStudent);

            cout << "\nStudent added succesfully!\n";
        }   

        else if (choice == 2) {
            if (students.empty())
            cout << "\nNo students found.\n";
            else {
                cout << "\n==========STUDENT LIST==========\n";

                for (int i = 0; students.size() ; i++) {
                    cout << "\n Student number" << i+1 << endl;
                    students[i].displayInfo();
                }
                }
            }
        } while (choice != 4);
    }


