#include <vector>
#include <iostream>
#include <set>
using namespace std;

void dfs(int node, int parent, int depth, int k, int root, const vector<vector<int>>& graph, long long& result, vector<vector<bool>>& excludes)
{
    if (depth == k)
    {
        if (!excludes[root][node])
        {
            excludes[root][node] = true;
            excludes[node][root] = true;
            result++;
        }
        return;
    }

    for (auto child : graph[node])
    {
        if (child == parent)
            continue;
        dfs(child, node, depth + 1, k, root, graph, result, excludes);
    }
}

long long distance(int n, int k, vector<vector<int>> edges)
{
    vector<vector<int>> graph(n + 1, vector<int>());

    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    vector<vector<bool>> excludes(n + 1, vector<bool>(n + 1, false));
    long long result = 0;
    for (int i = 1; i <= n; i++)
    {
        dfs(i, 0, 0, k, i, graph, result, excludes);
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
    vector<vector<int>> graph(n + 1, vector<int>());

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        edges.push_back({u, v});
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    auto res = ::distance(5, 2, {{1,2}, {2,3}, {3,4}, {2,5}});
}