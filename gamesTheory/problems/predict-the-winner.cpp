#include <vector>
using namespace std;

long long Solve(int left, int right, const vector<int>& nums, vector<vector<long long>>& dp)
{
    if (left > right)
        return 0;

    if (left == right)
        return nums[left];

    if (dp[left][right] != -1)
        return dp[left][right];

    long long leftRight = Solve(left + 1, right - 1, nums, dp);
    long long leftLeft = Solve(left + 2, right, nums, dp);
    long long rightRight = Solve(left, right - 2, nums, dp);

    //dp[left][right] = max({nums[left] + leftRight, nums[left] + leftLeft, nums[right] + leftRight, nums[right] + rightRight});
    dp[left][right] = max(nums[left] +  min(Solve(left + 2, right, nums, dp), Solve(left + 1, right - 1, nums, dp)),
                          nums[right] + min(Solve(left + 1, right - 1, nums, dp), Solve(left, right - 2, nums, dp)));

    return dp[left][right];
}

bool PredictTheWinner(vector<int> nums) 
{
    int sum = 0;
    for (auto n : nums)
        sum += n;

    vector<vector<long long>> dp(nums.size(), vector<long long>(nums.size(), -1));

    long long resA = Solve(0, nums.size() - 1, nums, dp);
    long long resB = sum - resA;

    return resA >= resB;
}