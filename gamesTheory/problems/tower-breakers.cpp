#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

vector<int> sieve(int n)
{
    vector<bool> primes(n + 1, true);
    vector<int> counts(n + 1, 0);

    for (int i = 2; i <= n; i++)
    {
        if (!primes[i])
        {
            continue;
        }

        // prime has count 1
        counts[i] = 1;
        for (int j = 2 * i; j <= n; j += i)
        {
            // this jj part is about adding all i's in factorization of j
            // for example 9 is 3 * 3, we need to add both 3s
            int jj = j;
            while(jj % i == 0)
            {
                counts[j]++;
                jj /= i;
            }
            primes[j] = false;
        }
    }

    return counts;
}

int towerBreakers(vector<int> arr, const vector<int>& counts)
{
    int nimSum = 0;
    for (auto n : arr)
        nimSum ^= counts[n];

    return nimSum == 0 ? 2 : 1;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    auto counts = sieve(1e6 + 1);

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;
        vector<int> towers(n, 0);
        for (int i = 0; i < n; i++)
        {
            cin >> towers[i];
        }
        cout << towerBreakers(towers, counts) << "\n";
    }
}