#include <iostream>
#include <vector>

using namespace std;

bool isPalindrome(const vector<int>& v) {
    int left = 0;
    int right = v.size() - 1;

    while (left < right) {
        if (v[left] != v[right])
            return false;

        left++;
        right--;
    }

    return true;
}


vector<int> findPairWithDifferenceK(const vector<int>& v, int k) {
    for (int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if (v[i] - v[j] == k || v[j] - v[i] == k)
                return {v[i], v[j]};
        }
    }

    return {};
}

int main () {
    vector <int> v1 = {1, 2, 3, 2, 1};

    if(isPalindrome (v1))
    cout << "V1 is Palindrome.\n";

    vector v2 = findPairWithDifferenceK (v1,2);

}