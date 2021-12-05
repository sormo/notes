#include <vector>
#include <string>
using namespace std;

string solve(int n,int a,int b, vector<int> A)
{
    int bobCount = 0;
    int aliceCount = 0;
    
    for (auto n : A)
    {
        if (n % a == 0)
            bobCount++;
        if (n % b == 0)
            aliceCount++;
    }
    
    bool aliceTurn = false;
    for (auto n : A)
    {
        if (n % a == 0 && n % b == 0)
        {
            aliceTurn = true;
            aliceCount--;
            bobCount--;
        }
    }
    
    if (aliceTurn)
        return aliceCount > bobCount ? "Alice" : "Bob";
    
    return bobCount > aliceCount ? "Bob" : "Alice";
}