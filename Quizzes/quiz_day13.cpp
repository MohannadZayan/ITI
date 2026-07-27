#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int NumberOfWords(const string& sentence)
{
    int wordCount = 1;

    for (char character : sentence)
    {
        if (character == ' ')
        {
            ++wordCount;
        }
    }

    return sentence.empty() ? 0 : wordCount;
}

void PrintMissingElements(const vector<int>& vec, int min, int max)
{
    unordered_set<int> elements(vec.begin(), vec.end());

    cout << "Missing elements: ";
    bool hasMissing = false;

    for (int i = min; i <= max; ++i)
    {
        if (elements.find(i) == elements.end())
        {
            if (hasMissing)
            {
                cout << ", ";
            }
            cout << i;
            hasMissing = true;
        }
    }

    if (!hasMissing)
    {
        cout << "None";
    }
}

int main()
{
    string sentence = "C plus plus is fun";
    vector<int> numbers = {1, 2, 5, 6};

    cout << "Number of words: " << NumberOfWords(sentence) << '\n';
    PrintMissingElements(numbers, 1, 6);
    cout << '\n';

    return 0;
}
