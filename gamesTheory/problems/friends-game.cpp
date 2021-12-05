#include <vector>
#include <iostream>
using namespace std;

string solve(int n, vector<int> stones, vector<vector<int>> edges)
{
    int nimSum = 0;
    for (auto s : stones)
        nimSum ^= s;

    return nimSum == 0 ? "Ross" : "Rachel";
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cout << solve(5, {5, 6, 7, 19, 3}, {{1,2}, {1,3}, {1,4}, {2,5}});
}