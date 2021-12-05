#include <vector>
#include <iostream>
using namespace std;

int countNumberOfWaysToWin(vector<int>& boxes)
{
    int nimSum = 0;
    for (auto box : boxes)
        nimSum ^= box;

    int result = 0;
    for (auto box : boxes)
    {
        if ((nimSum ^ box) < box)
            result++;
    }
    return result;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    vector<int> boxes(n);
    for (int i = 0; i < n; i++)
        cin >> boxes[i];

    cout << countNumberOfWaysToWin(boxes);
}