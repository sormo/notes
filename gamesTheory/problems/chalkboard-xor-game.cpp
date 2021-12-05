#include <vector>
#include <iostream>
#include <map>
#include <set>
using namespace std;

const int M = 17;

int xorValue(const vector<int>& nums)
{
    int result = 0;
    for (auto v : nums)
        result ^= v;
    return result;
}

int mex(const set<int>& nums)
{
    int result = 0;
    while(true)
    {
        if (!nums.contains(result))
            return result;
        result++;
    }
    return result;
}

int spragueGrundy(vector<int> state, map<vector<int>, int>& mem)
{
    if (mem.contains(state))
        return mem[state];

    // terminal positions
    if (state.empty() || xorValue(state) == 0)
        return mem[state] = xorValue;

    set<int> spragueGrundyValues;
    // find grundy values for states reachable from this state:
    for (size_t i = 0; i < state.size(); i++)
    {
        vector<int> newState(state);
        newState.erase(begin(newState) + i);

        spragueGrundyValues.insert(spragueGrundy(newState, mem));
    }

    return mem[state] = mex(spragueGrundyValues);
}

bool xorGame(vector<int> nums)
{
    map<vector<int>, int> mem;
    return spragueGrundy(nums, mem) != 0;
}

bool xorGameTest(vector<int> nums)
{
    int val = 0; 
    for (auto& x : nums) val ^= x; 
    return val == 0 || size(nums) % 2 == 0; 
}

int main()
{
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    cout << xorGameTest({4,5,8,10,5,22,6,8,7,1,2,3,4,6,9,8});
    cout << xorGame({4,5,8,10,5,22,6,8,7,1,2,3,4,6,9,8});
}
