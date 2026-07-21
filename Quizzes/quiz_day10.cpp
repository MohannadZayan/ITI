#include<iostream>
#include <vector>
#include <algorithm>

using namespace std;

int FindMissing (const vector <int> numbers) {
    int i = 0;

    for (int num : numbers) {
        if (num != i) {
            return i;
        }
        i++;
    }
    return i;
}
char NonRepeating (const string & str) {
    int count [300] = {0};

    for (char c : str) {
        count [c] ++;
    }

    for (char c : str) {
        if (count [c] == 1)
        return c;
    }

    return '0';
}


int main () {
    vector <int> numbers;
    int size;
    int num;

    cout << "Enter the number of elements: ";
    cin >> size;

    cout <<"Enter the numbers: \n";

    for (int i =0; i <size; i++) {
        cout << "Element number " << i+1 << ": ";
        cin >> num;
        numbers.push_back(num);
    }

    cout << "The missing number is: " << FindMissing(numbers) << endl;

    cin.ignore();

    string str;

    cout << "Enter a string : ";
    getline (cin,str);

    char result = NonRepeating(str);

    if (result != '0')
    cout << "First non-repeating character: " << result << endl;

    else
    cout << "No non repeating character.\n";


    return 0;
}