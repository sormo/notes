#include <vector>
#include <iostream>
#include <string>
using namespace std;

string decideWinner(int n)
{
    if (n == 1)
        return "Kitty";
    
    if (n % 2 == 0)
        return "Kitty";
    return "Katty";
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        cout << decideWinner(n) << "\n";
    }
}
