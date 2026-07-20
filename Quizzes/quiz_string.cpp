#include <iostream>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;


void ReverseString () {
    string s;
    cout << "Enter a string: ";
    getline (cin,s);

    reverse (s.begin(),s.end());
    int start = 0;

    for (int i = 0; i <=s.length() ; i++) {

        if (i == s.length() || s[i] == ' ') {
            reverse (s.begin() + start, s.begin() + i);
            start = i+1;
        }
    }
    cout << s << endl;
}

void PrintEverySecond () {
    while (1){
        cout << "Hello World\n";
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main () {
    ReverseString();
    PrintEverySecond();

    return 0;
}