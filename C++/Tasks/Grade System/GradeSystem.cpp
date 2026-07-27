#include <iostream>
using namespace std;

int readGrade() {
    
    int grade[5];
    int sum = 0;

    for (int i = 0; i < 5; ) {
    try {
        cout << "Enter grade " << i + 1 << ": ";
        cin >> grade[i];

        if (grade[i] < 0 || grade[i] > 100)
            throw invalid_argument("Grade must be between 0 and 100.");

        sum += grade[i];
        i++;
    }
    catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }
}
    return sum;
}

double avg(int total) {
    return static_cast<double>(total) / 5;
}

int main () {
    string name;
    cout << "Enter your name: ";
    getline(cin, name);
    if (name.empty()) {
        cout << "Name cannot be empty." << endl;
        return 1;
    }

    int total;

try {
    total = readGrade();
} catch (const invalid_argument& e) {
    cout << e.what() << endl;
    return 1;
}

cout << "Hello, " << name << "!" << endl;
cout << "--------------Result-------------------" << endl;
    
    cout << "The total grade is: " << total << "Out of 500." << endl;
    if (total >= 90) {
        cout << "Grade: A" << endl;
    } else if (total >= 80) {
        cout << "Grade: B" << endl;
    } else if (total >= 70) {
        cout << "Grade: C" << endl;
    } else if (total >= 60) {
        cout << "Grade: D" << endl;
    } else {
        cout << "Grade: F" << endl;
    }

    cout << "The average grade is: " << avg(total) << "%" << endl;
    return 0;
}