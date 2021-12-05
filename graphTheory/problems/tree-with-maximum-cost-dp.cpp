#include <vector>
#include <iostream>
using namespace std;

void dfs(int node, int parent, vector<int>& distances, const vector<int>& a, const vector<vector<int>>& graph)
{
    distances[node] = ;

    for (int child : graph[node])
    {
        if (child == parent)
            continue;
        dfs(child, node, distances, a, graph);
    }
}

long long treeMaxCost(int n, vector<int> a ,vector<vector<int>> edges)
{
    vector<vector<int>> graph(n + 1, vector<int>());
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    long long result = 0;
    for (int i = 1; i <= n; i++)
    {
        long long res = 0;
        dfs(i, 0, 0, a, graph, res);

        result = max(res, result);
    }

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

    auto res = treeMaxCost(8, {9,4,1,7,10,1,6,5}, edges);
}