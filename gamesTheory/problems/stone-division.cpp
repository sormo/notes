#include <vector>
#include <iostream>
#include <set>
#include <map>
using namespace std;

#define int int64_t

map<int, int> memo;

int mex(const set<int>& states)
{
    int result = 0;
    while(states.find(result) != states.end())
        result++;
    return result;
}

int grundy(int pile, const vector<int>& numbers)
{
    if (memo.count(pile))
        return memo[pile];

    set<int> states;

    for (auto n : numbers)
    {
        if (pile % n == 0)
        {
            int newPileCount = pile / n;
            if (newPileCount % 2 == 0)
                states.insert(0);
            else
                states.insert(grundy(newPileCount, numbers));
        }
    }

    return memo[pile] = mex(states);
}

int32_t main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int m, n;
    cin >> n >> m;

    vector<int> numbers(m);
    for (int i = 0; i < m; i++)
        cin >> numbers[i];

    cout << (grundy(n, numbers) == 0 ? "Second" : "First") << "\n";
}