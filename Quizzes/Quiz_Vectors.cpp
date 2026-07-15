#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void MaxMin(vector<int>& vec, int* max, int* min)
{
    auto min_it = min_element(vec.begin(), vec.end());
    auto max_it = max_element(vec.begin(), vec.end());

    *min = *min_it;
    *max = *max_it;
}

bool Equal (vector <int> vec1, vector <int> vec2) {

auto it1 = vec1.begin();
auto it2 = vec2.begin();

   while (it1 != vec1.end()) {
    if (*it1 != *it2)
    return false;

    it1++;
    it2++;
   }

   return true;
}

void ReverseVector (vector <int> &vec) {
    auto start = vec.begin();
    auto end = vec.end () -1;

    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}

void PrintVector(vector<int>& vec)
{
    for (auto it = vec.begin(); it != vec.end(); it++)
    {
        cout << *it << " ";
    }

    cout << endl;
}

bool HasDuplicate(vector<int>& vec)
{
    for (int i = 0;i < vec.size(); i++)
    {
        for (int j= i + 1; j < vec.size(); j++)
        {
            if (vec[i] == vec[j])
            {
                return true;
            }
        }
    }

    return false;
}


int main()
{
    int max, min;

    vector<int> vec1 = {1, 2, 3, 4, 5, 5};
    vector<int> vec2 = {1, 2, 3, 4, 5, 5};

    cout << "=====VECTOR 1=====\n";

    MaxMin(vec1, &max, &min);
    cout << "Max: " << max << endl;
    cout << "Min: " << min << endl;

    cout << "Vector before: ";
    PrintVector(vec1);

    ReverseVector(vec1);

    cout << "Vector after: ";
    PrintVector(vec1);

    if (HasDuplicate(vec1))
    cout << "Has duplicates.\n";
    else
    cout << "No duplicates.\n";

    //================= VECTOR 2 =================


    cout << "=====VECTOR 2=====\n";

    MaxMin(vec2, &max, &min);
    cout << "Max: " << max << endl;
    cout << "Min: " << min << endl;

    cout << "Vector before: ";
    PrintVector(vec2);

    ReverseVector(vec2);

    cout << "Vector after: ";
    PrintVector(vec2);

    if (HasDuplicate(vec2))
    cout << "Has duplicates.\n";
    else
    cout << "No duplicates.\n";




    if (Equal(vec1, vec2))
        cout << "The vectors are equal.\n";
    else
        cout << "Not equal.\n";

    return 0;
}