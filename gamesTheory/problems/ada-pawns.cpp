#include <vector>
#include <string>
#include <iostream>
#include <set>
using namespace std;

string solve(string board)
{
    vector<int> piles;
    int pile = 0;
    for (int i = 0; i < board.size(); i++)
    {
        if (board[i] == 'P')
        {
            piles.push_back(pile);
            pile = 0;
        }
        else
        {
            pile++;
        }
    }

    reverse(begin(piles), end(piles));

    int nimSum = 0;
    for (int i = 0; i < piles.size(); i += 2)
    {
        nimSum ^= (piles[i] % 3);
    }

    return nimSum == 0 ? "No" : "Yes";
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    string row;
    cin >> row;

    cout << solve(row);
}