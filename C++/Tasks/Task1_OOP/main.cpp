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

int main()
{
    vector<Student> students;
    int choice;

    do
    {
        cout << "\n========== STUDENT MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search for a Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        if (choice == 1)
        {
            int id;
            string name;
            int age;
            string major;
            double gpa;

            // Student ID
            cout << "\nEnter Student ID: ";

            while (!(cin >> id))
            {
                cout << "Invalid ID. Please enter a number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            cin.ignore(1000, '\n');

            // Student Name
            cout << "Enter Student Name: ";
            getline(cin, name);

            while (name.empty())
            {
                cout << "Name cannot be empty. Enter Student Name: ";
                getline(cin, name);
            }

            // Student Age
            cout << "Enter Student Age: ";

            while (!(cin >> age) || age <= 0)
            {
                cout << "Invalid age. Please enter a valid number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            cin.ignore(1000, '\n');

            // Student Major
            cout << "Enter Student Major: ";
            getline(cin, major);

            while (major.empty())
            {
                cout << "Major cannot be empty. Enter Student Major: ";
                getline(cin, major);
            }

            // Student GPA
            cout << "Enter Student GPA (0.0 - 4.0): ";

            while (!(cin >> gpa) || gpa < 0.0 || gpa > 4.0)
            {
                cout << "Invalid GPA. Please enter a GPA between 0.0 and 4.0: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            Student newStudent(id, name, age, major, gpa);

            students.push_back(newStudent);

            cout << "\nStudent added successfully!\n";
        }

        else if (choice == 2)
        {
            if (students.empty())
            {
                cout << "\nNo students found.\n";
            }
            else
            {
                cout << "\n========== STUDENT LIST ==========\n";

                for (int i = 0; i < students.size(); i++)
                {
                    cout << "\nStudent number " << i + 1 << endl;
                    cout << "--------------------------\n";

                    students[i].displayInfo();
                }
            }
        }

        else if (choice == 3)
        {
            int searchId;
            bool found = false;

            cout << "\nEnter Student ID to search: ";

            while (!(cin >> searchId))
            {
                cout << "Invalid ID. Please enter a number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            for (int i = 0; i < students.size(); i++)
            {
                if (students[i].getID() == searchId)
                {
                    cout << "\nStudent found!\n";
                    cout << "--------------------------\n";

                    students[i].displayInfo();

                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "\nStudent not found.\n";
            }
        }

        else if (choice == 4)
        {
            cout << "\nExiting Student Management System...\n";
        }

        else
        {
            cout << "\nInvalid choice. Please select from 1 to 4.\n";
        }

    } while (choice != 4);

    return 0;
}


