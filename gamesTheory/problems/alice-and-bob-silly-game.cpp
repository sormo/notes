#include <vector>
#include <iostream>
using namespace std;

vector<int> primes(int n)
{
    vector<int> result;
    vector<bool> sieve(n + 1, false);
    for (int i = 2; i <= n; i++)
    {
        if (sieve[i])
            continue;
        result.push_back(i);
        for (int j = i; j <= n; j += i)
        {
            sieve[j] = true;
        }
    }
    return result;
}

string solve(int n)
{
    auto p = primes(n);
    
    if (p.size() == 0)
        return "Bob";
    
    return p.size() % 2 == 0 ? "Bob" : "Alice";
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

        cout << solve(n) << "\n";
    }
}