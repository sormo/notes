#include <vector>
#include <algorithm>
using namespace std;

int maxCoins(vector<int> piles)
{
    sort(piles.rbegin(), piles.rend());
    
    int res = 0;
    for (int i = 1; i < 2 * piles.size() / 3; i += 2)
        res += piles[i];
        
    return res;
}
