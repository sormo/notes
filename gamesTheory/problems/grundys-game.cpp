#include <vector>
#include <set>
#include <map>
#include <iostream>
using namespace std;

int mex(const set<int>& states)
{
    int result = 0;
    while(states.find(result) != states.end())
        result++;
    return result;
}

int grundy(int pile, map<int, int>& memo)
{
    if (memo.count(pile))
        return memo[pile];

    // if (pile == 1)
    //     return 0;

    set<int> states;
    for (int i = 1; i <= pile / 2; i++)
    {
        if (i != pile - i)
            states.insert(grundy(i, memo) ^ grundy(pile - i, memo));
    }

    return memo[pile] = mex(states);
}

int grundyDp(int pile)
{
    vector<int> dp(pile + 1, 0);
    for (int i = 3; i <= pile; i++)
    {
        set<int> states;
        for (int j = 1; j <= i / 2; j++)
        {
            states.insert(dp[j] ^ dp[i - j]);
        }
        dp[i] = mex(states);
    }
    return dp[pile];
}

string solve(int n)
{
    map<int, int> memo;
    int value = grundyDp(10e6);

    for (int i = 0; i < 30; i++)
        cout << i << " " << grundyDp(i) << "\n";

    return value == 0 ? "second" : "first";
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cout << solve(15);
}
