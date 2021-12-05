#include <vector>
#include <set>
#include <iostream>
using namespace std;

int grundy(int n)
{
    if (n == 0 || n == 1)
        return 0;

    set<int> S;
    for (int i = n; i >= ceil(n / 2); i--)
        S.insert(grundy(n - i));

    int mex = 0;
    while(true)
    {
        if (S.contains(mex))
            mex++;
        else
            return mex;
    }
}

int main()
{
    for (int i = 0; i <= 15; i++)
        cout << i << " -> " << grundy(i) << "\n";
}