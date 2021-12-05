#include <vector>
#include <iostream>
#include <set>
using namespace std;

int mex(const set<int>& states)
{
    int result = 0;
    while(states.find(result) != states.end())
        result++;
    return result;
}

vector<vector<int>> sieve(int n)
{
    vector<vector<int>> divisors(n + 1, vector<int>());

    for (int i = 2; i < n; i++)
    {
        for (int j = i; j < n; j += i)
            divisors[j].push_back(i);
    }

    return divisors;
}

int grundy(int tower, const vector<vector<int>>& divisors)
{
    if (tower == 1)
        return 0;

    set<int> states;
    for (auto y : divisors[tower])
    {
        int z = tower / y;
        // if tower is divided into even number of smaller towers, all smaller towers cancels out
        // if tower is divided into odd number of smaller towers, all cancels out except the last one (for example in 5 four wil cancel out)
        if (y % 2 == 0)
            states.insert(0);
        else
            states.insert(grundy(z, divisors));
    }

    return mex(states);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    auto divisors = sieve(1e6 + 1);

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        
        vector<int> towers(n);
        for (int i = 0; i < n; i++)
            cin >> towers[i];

        int nimSum = 0;
        for (auto tower : towers)
            nimSum ^= grundy(tower, divisors);

        cout << (nimSum == 0 ? "2" : "1") << "\n";
    }
}
