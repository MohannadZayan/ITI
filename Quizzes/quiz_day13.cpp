#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

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

void PrintMissingElements(const vector<int>& numbers)
{
    if (numbers.empty())
    {
        return;
    }

    vector<int> sortedNumbers = numbers;
    sort(sortedNumbers.begin(), sortedNumbers.end());

    cout << "Missing elements: ";

    int i = sortedNumbers.front();

    for (int number : sortedNumbers)
    {
        while (i < number)
        {
            cout << i << ' ';
            ++i;
        }

        if (i == number)
        {
            ++i;
        }
    }
}

int main()
{
    string sentence = "C plus plus is fun";
    vector<int> numbers = {1, 2, 5, 6};

    cout << "Number of words: " << NumberOfWords(sentence) << '\n';
    PrintMissingElements(numbers);
    cout << '\n';

    return 0;
}
