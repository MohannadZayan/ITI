#include <iostream>
#include <string>

using namespace std;

void inputMarks(int *math, int *physics, int *english);

double calculateAverage(int *math, int *physics, int *english);

char calculateGrade(double average);

void printReport(string name, int *math, int *physics, int *english);

int main()
{
    string name;
    int math, physics, english;
    int choice;

    cout << "Enter student name: ";
    getline(cin, name);

    inputMarks(&math, &physics, &english);

    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Update Math\n";
        cout << "2. Update Physics\n";
        cout << "3. Update English\n";
        cout << "4. Show Average\n";
        cout << "5. Print Report\n";
        cout << "6. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice! Please enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            while (true)
            {
                cout << "Enter new Math mark: ";
                cin >> math;

                if (cin.fail() || math < 0 || math > 100)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid mark! Please enter a value between 0 and 100.\n";
                }
                else
                {
                    break;
                }
            }
            break;

        case 2:
            while (true)
            {
                cout << "Enter new Physics mark: ";
                cin >> physics;

                if (cin.fail() || physics < 0 || physics > 100)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid mark! Please enter a value between 0 and 100.\n";
                }
                else
                {
                    break;
                }
            }
            break;

        case 3:
            while (true)
            {
                cout << "Enter new English mark: ";
                cin >> english;

                if (cin.fail() || english < 0 || english > 100)
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid mark! Please enter a value between 0 and 100.\n";
                }
                else
                {
                    break;
                }
            }
            break;

        case 4:
            cout << "Average = "
                 << calculateAverage(&math, &physics, &english) << endl;
            cout << "Grade = "
                 << calculateGrade(calculateAverage(&math, &physics, &english))
                 << endl;
            break;

        case 5:
            printReport(name, &math, &physics, &english);
            break;

        case 6:
            cout << "Goodbye!\n";
            break;

        default:
            cout << "Invalid menu choice!\n";
        }

    } while (choice != 6);

    return 0;
}

void inputMarks(int *math, int *physics, int *english)
{
    while (true)
    {
        cout << "Enter Math mark: ";
        cin >> *math;

        if (cin.fail() || *math < 0 || *math > 100)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid mark! Please enter a value between 0 and 100.\n";
        }
        else
        {
            break;
        }
    }

    while (true)
    {
        cout << "Enter Physics mark: ";
        cin >> *physics;

        if (cin.fail() || *physics < 0 || *physics > 100)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid mark! Please enter a value between 0 and 100.\n";
        }
        else
        {
            break;
        }
    }

    while (true)
    {
        cout << "Enter English mark: ";
        cin >> *english;

        if (cin.fail() || *english < 0 || *english > 100)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid mark! Please enter a value between 0 and 100.\n";
        }
        else
        {
            break;
        }
    }
}

double calculateAverage(int *math, int *physics, int *english)
{
    return (*math + *physics + *english) / 3.0;
}

char calculateGrade(double average)
{
    if (average >= 90)
        return 'A';
    else if (average >= 80)
        return 'B';
    else if (average >= 70)
        return 'C';
    else if (average >= 60)
        return 'D';
    else
        return 'F';
}

void printReport(string name, int *math, int *physics, int *english)
{
    double average = calculateAverage(math, physics, english);
    char grade = calculateGrade(average);

    cout << "\n===== Student Report =====\n";
    cout << "Student : " << name << endl;
    cout << "Math    : " << *math << endl;
    cout << "Physics : " << *physics << endl;
    cout << "English : " << *english << endl;
    cout << "Average : " << average << endl;
    cout << "Grade   : " << grade << endl;
}