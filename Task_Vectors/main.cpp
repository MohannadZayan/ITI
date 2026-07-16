#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void PrintVector (const vector <int> &vec) {
    for (int num: vec) {
        cout << num << " ";
    }
}
void ReverseInPlace ( vector <int> &vec) {
       int left = 0;
       int right = vec.size() - 1;
       while (left < right) {
        swap (vec[left],vec[right]);
        left++;
        right--;
     } 
    }

void Frequency (const vector <int> &vec) {
    for (int num : vec) {
        int frequency = count (vec.begin(), vec.end(), num);
        cout << num << " Occurs " << frequency << " time(s)." << endl;
    }
}

int SecondLargest ( vector <int> &vec) {
    sort(vec.begin(), vec.end());
    int largest = *(vec.end()-1);
    for (int i = vec.size()-2; i>=0; i--) {
        if (vec[i] != largest) {
            return vec[i];
        }
    }
    return -1;
}

void RemoveDuplicates ( vector<int> &vec) {
    sort (vec.begin(), vec.end());

        auto it = unique (vec.begin(), vec.end());
        vec.erase (it, vec.end());
    

    for (int num: vec) {
        cout << num << " ";
    }
}

int main () {
 vector<int> vec1 = {1, 5, 3, 5, 8, 2, 8};


//=========== VECTOR 1 ==========
cout << "Vector 1: " << endl;
PrintVector(vec1);
cout << endl;

cout << "Reversed in place: ";
ReverseInPlace(vec1);
PrintVector (vec1);
cout << endl;

cout << "Frequency: " << endl;
Frequency(vec1);
cout << endl;

cout << "Removed duplicates: ";
RemoveDuplicates(vec1);
}