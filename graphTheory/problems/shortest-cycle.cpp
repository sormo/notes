#include <vector>
using namespace std;

int dfs(int node, int parent, const vector<vector<int>>& graph, vector<bool>& visited, int length)
{
    visited[node] = true;

    int result = numeric_limits<int>::max();

    for (int child : graph[node])
    {
        if (child == parent)
            continue;
        
        if (visited[child])
            result = min(result, length);
        else
            result = min(result, dfs(child, node, graph, visited, length + 1));
    }

    visited[node] = false;

    return result;
}

int solve(int n, vector<vector<int>> edges)
{
    vector<vector<int>> graph(n+1, vector<int>());

    for (const auto &e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    int result = numeric_limits<int>::max();

    vector<bool> visited(n + 1, false);

    for (int i = 1; i <= n; i++)
    {
        result = min(result, dfs(i, -1, graph, visited, 1));
    }

    return result == numeric_limits<int>::max() ? -1 : result;
}