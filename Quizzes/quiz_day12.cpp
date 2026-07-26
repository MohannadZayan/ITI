#include <iostream>
#include <vector>

using namespace std;

// Assumes the vector is sorted and contains at least two elements.
pair<int, int> closestPairToZero(const vector<int>& numbers)
{
    size_t left = 0;
    size_t right = numbers.size() - 1;
    pair<int, int> closestPair = {numbers[left], numbers[right]};
    int smallestDistance = abs(numbers[left] + numbers[right]);

    while (left < right)
    {
        int sum = numbers[left] + numbers[right];
        int distance = abs(sum);

        if (distance < smallestDistance)
        {
            smallestDistance = distance;
            closestPair = {numbers[left], numbers[right]};
        }

        if (sum == 0)
        {
            return {numbers[left], numbers[right]};
        }

        if (sum < 0)
        {
            ++left;
        }
        else
        {
            --right;
        }
    }

    return closestPair;
}
