#include <vector>
#include <set>
using namespace std;

void dfs(int node, int parent, const vector<vector<int>>& graph, const vector<int>& colors, vector<set<int>>& dp)
{
    for (auto child : graph[node])
    {
        if (child == parent)
            continue;
        dfs(child, node, graph, colors, dp);

        for (auto c : dp[child])
            dp[node].insert(c);
    }

    dp[node].insert(colors[node-1]);
}

vector<int> solve(int n, vector<int> a, vector<vector<int>> edges)
{
    vector<int> inTime(n + 1, 0);
    vector<int> outTime(n + 1, 0);

    vector<vector<int>> graph(n + 1, vector<int>());
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    vector<set<int>> dp(n + 1, set<int>());
    dfs(1, 0, graph, a, dp);

    vector<int> result(n, 0);
    for (int i = 1; i <= n; i++)
    {
        result[i - 1] = dp[i].size();
    }
    return result;
}

int main()
{
    auto ret = solve(5, {2,3,2,2,1}, {{1,2}, {1,3}, {3,4}, {3,5}});
}
