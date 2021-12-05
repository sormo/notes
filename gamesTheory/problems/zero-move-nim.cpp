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

int grundy(int pile, bool hasZeroMove)
{
    if (pile == 0)
        return 0;

    set<int> states;
    for (int i = 0; i < pile; i++)
        states.insert(grundy(i, hasZeroMove));
    
    if (hasZeroMove)
        states.insert(grundy(pile, false));

    return mex(states);
}

int grundy2(int pile)
{
    if (pile == 0)
        return 0;

    if (pile % 2 == 0)
        return pile - 1;
    return pile + 1;
}

char zeroMoveNim(vector<int>& piles)
{
    int nimSum = 0;
    for (const auto& pile : piles)
        nimSum ^= grundy2(pile);
        //nimSum ^= grundy(pile, true);

    return nimSum == 0 ? 'L' : 'W';
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    for (int i = 0; i < 20; i++)
         cout << i << " " << grundy(i, true) << "\n";

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;

        vector<int> piles(n);
        for (int i = 0; i < n; i++)
            cin >> piles[i];

        cout << zeroMoveNim(piles) << "\n";
    }
}