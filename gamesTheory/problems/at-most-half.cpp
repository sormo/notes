#include <vector>
#include <set>
#include <iostream>
using namespace std;

int grundy(int n)
{
    if (n == 0 || n == 1)
        return 0;

    set<int> S;
    for (int i = 1; i <= floor(n / 2); i++)
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
    for (int i = 0; i <= 16; i++)
        cout << i << " -> " << grundy(i) << "\n";
}