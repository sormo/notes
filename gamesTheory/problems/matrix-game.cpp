#include <vector>
#include <iostream>
#include <map>
#include <set>
using namespace std;

int grundy(const vector<int>& row)
{
    int lastGrundy = row[row.size() - 1];

    for (int i = row.size() - 2; i >= 0; i--)
    {
        if (lastGrundy >= row[i])
            lastGrundy = row[i] - 1;
        else
            lastGrundy = row[i];
    }

    return lastGrundy;
}

string solve(int n, int m, vector<vector<int>> mat)
{
    int result = 0;
    for (auto& row : mat)
        result ^= grundy(row);

    return result == 0 ? "Second" : "First";
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cout << solve(2,2,{{2, 3}, {2, 3}});
}
