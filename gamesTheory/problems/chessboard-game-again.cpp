#include <vector>
#include <iostream>
#include <set>
#include <map>
using namespace std;

int mex(const set<int>& states)
{
    int result = 0;
    while(states.find(result) != states.end())
        result++;
    return result;
}

int dx[] = {-2, -2, 1, -1};
int dy[] = {1, -1, -2, -2};

int grundy(int x, int y, map<pair<int, int>, int>& memo)
{
    if (memo.count({x, y}))
        return memo[{x, y}];

    set<int> states;
    for (int i = 0; i < 4; i++)
    {
        int xx = x + dx[i];
        int yy = y + dy[i];

        if (xx >= 1 && yy >= 1 && xx <= 15 && yy <= 15)
            states.insert(grundy(xx, yy, memo));
    }

    return memo[{x, y}] = mex(states);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    map<pair<int, int>, int> memo;

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;

        int nimSum = 0;
        for (int i = 0; i < n; i++)
        {
            int x, y;
            cin >> x >> y;

            nimSum ^= grundy(x, y, memo);
        }

        cout << (nimSum == 0 ? "Second" : "First") << "\n";
    }
}