#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void dfs(int node, int parent, const vector<vector<pair<int, int>>>& graph, vector<int>& dp)
{
    for (int i = 0; i < graph[node].size(); i++)
    {
        int child = graph[node][i].first;
        int weight = graph[node][i].second;

        if (child != parent)
        {
            dfs(child, node, graph, dp);
            dp[node] += dp[child] + weight;
        }
    }
}

void dfsReRoot(int node, int parent, vector<int>& dp, const vector<vector<pair<int, int>>>& graph, const vector<vector<int>>& graphMatrix, int minimumValue, vector<int>& result)
{
    // cout << node << " " << dp[node] << "\n";
    // for (auto v : dp)
    //     cout << v << " ";
    // cout << "\n";

    if (dp[node] <= minimumValue)
    {
        if (dp[node] < minimumValue)
        {
            result.clear();
            minimumValue = dp[node];
        }
        result.push_back(node);
    }

    for (auto [child, weight] : graph[node])
    {
        if (child == parent)
            continue;

        // disconnect child from node
        dp[node] -= dp[child];
        dp[node] -= graphMatrix[node][child];
        // connect node to child (making the child parent)
        dp[child] += dp[node];
        dp[child] += graphMatrix[child][node];

        dfsReRoot(child, node, dp, graph, graphMatrix, minimumValue, result);

        // revert back
        dp[child] -= graphMatrix[child][node];
        dp[child] -= dp[node];
        dp[node] += graphMatrix[node][child];
        dp[node] += dp[child];
    }
}

vector<int> choosingCapital(int n, vector<vector<int>> edges)
{
    vector<vector<pair<int, int>>> graph(n + 1, vector<pair<int, int>>());
    vector<vector<int>> graphMatrix(n + 1, vector<int>(n + 1, 0));

    for (const auto& e : edges)
    {
        graph[e[0]].push_back({e[1], 0});
        graph[e[1]].push_back({e[0], 1});
        graphMatrix[e[1]][e[0]] = 1;
    }

    vector<int> dp(n + 1, 0);
    dfs(1, 0, graph, dp);

    vector<int> result;
    int minValue = numeric_limits<int>::max();
    dfsReRoot(1, 0, dp, graph, graphMatrix, minValue, result);

    sort(begin(result), end(result));

    return result;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n;

    m = n - 1;

    vector<vector<int>> edges;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        edges.push_back({u, v});
    }

    auto res = choosingCapital(4, edges);

    for (auto i : res)
        cout << i << " ";
}