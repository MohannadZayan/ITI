#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void PrintVector(const vector <int> &vec) {
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

void Merge (const vector <int> &vec1, const vector<int> &vec2, vector <int> &vec3) {
    int i = 0;
    int j = 0;
    int k = 0;

    vec3.resize (vec1.size() + vec2.size());

    while ( i < vec1.size() && j < vec2.size()) {
        if (vec1[i] < vec2 [j]) {
            vec3[k] = vec1[i];
            i++;
        }
        else {
            vec3[k] = vec2[j];
            j++;
        }
        k++;

    }
    while (i < vec1.size()) {
        vec3[k] = vec1[i];
        i++;
        k++;
    }

    while ( j < vec2.size()) {
        vec3[k] = vec2[j];
        j++;
        k++;
    }
}

void RemoveNeg ( vector <int> &vec) {
    erase_if (vec, [] (int num) {
        return num < 0;

    });
}

bool CheckSum (const vector <int> &vec1, const vector <int> &vec2) {
    double sum1 = 0;
    double sum2= 0;

    for (int num: vec1) {
        sum1+= num;
    }
    for (int num : vec2) {
        sum2+= num;
    }

    return sum1 == sum2;
}

int CountVowels (const string &text) {
    int count = 0;

    for (char ch : text) {
        if (string("eauoiEAUOI").find(ch) != string::npos)
        count++;
    }
    return count;
}
void ReverseString ( string &text) {
    int left = 0;
    int right = text.size() -1;

    while (left < right) {
        swap(text[left] , text[right]);

        left++;
        right--;
    }
}

int main () {
    vector <int> vec1 = {1, 3, 5, 7};
    vector <int> vec2 = {2, 4, 6, 8};
    vector <int> vec3;
//MERGE FUNCTION
cout << "===== MERGE =====" << endl;
    Merge (vec1, vec2, vec3);

    cout << "Vector 1: ";
    PrintVector (vec1);
    cout << "Vector 2: ";
    PrintVector(vec2);

    cout << "Merged vector: ";
    PrintVector(vec3);

//REMOVE NEG
cout << "=====REMOVE NEGATIVE=====" << endl;
vector <int> vec4 = {5,-2,8,-7,3,-1,10};

cout << "Vector before: ";
PrintVector(vec4);

RemoveNeg(vec4);

cout << "Vector after: ";
PrintVector(vec4);

//CHECKSUM
cout << "=====CHECK SUM=====" << endl;

vector <int> vec5 = {1,2,3};
vector <int> vec6 = {4,2};

if (CheckSum(vec5,vec6))
cout << "Equal sum." << endl;
else
cout << "Not equal sum." << endl;


//COUNT VOWELS

cout << "=====COUNT VOWELS=====" << endl;

string text;
cout << "Enter a string: ";
getline (cin,text);
cout << "Number of vowels: " << CountVowels(text) << endl;


cout << "=====REVERSE STRING===== << " << endl;

cout << "Before reversing: " << text << endl;

ReverseString(text);

cout << "After reversing: " << text << endl;
    
}