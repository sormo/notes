#include <vector>
#include <set>
#include <iostream>
using namespace std;

int mex(const set<int>& states)
{
    int result = 0;
    while(states.find(result) != end(states))
        result++;
    return result;
}

const int dx[] = { -2, -2,  1, -1 };
const int dy[] = {  1, -1, -2, -2 };

int solve(int x, int y)
{
    set<int> states;
    for (int i = 0; i < 4; i++)
    {
        int xx = x + dx[i];
        int yy = y + dy[i];

        if (xx < 1 || xx > 15 || yy < 1 || yy > 15)
            continue;
        states.insert(solve(xx, yy));
    }

    return mex(states);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t;
    cin >> t;
    while(t--)
    {
        int x, y;
        cin >> x >> y;

        if (solve(x, y) == 0)
            cout << "Second\n";
        else
            cout << "First\n";
    }
}
