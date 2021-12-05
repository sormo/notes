#include <vector>
#include <iostream>
using namespace std;

void dfs(int node, int parent, vector<int>& maxw, const vector<vector<int>>& graph, const vector<int>& a)
{
    maxw[node] = a[node - 1] == 0 ? -1 : 1;

    for (int child : graph[node])
    {
        if (child != parent)
        {
            dfs(child, node, maxw, graph, a);
            maxw[node] += max(maxw[child], 0);
        }
    }
}

void dfsReroot(int node, int parent, vector<int>& maxw, const vector<vector<int>>& graph, vector<int>& result)
{
    result[node - 1] = maxw[node];

    for (auto child : graph[node])
    {
        if (child == parent)
            continue;
        maxw[node] -= max(maxw[child], 0);
        maxw[child] += max(maxw[node], 0);

        dfsReroot(child, node, maxw, graph, result);

        maxw[child] -= max(maxw[node], 0);
        maxw[node] += max(maxw[child], 0);
    }
}

vector<int> maxWhiteSubtree(int n, vector<int> a, vector<vector<int>> edges)
{
    vector<vector<int>> graph(n + 1, vector<int>());
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    // O(n*n)
    vector<int> result(n, 0);
    // for (int i = 1; i <= n; i++)
    // {
    //     vector<int> maxw(n + 1, 0);
    //     dfs(i, 0, maxw, graph, a);

    //     result[i - 1] = maxw[i];
    // }

    // O(n)
    {
        vector<int> maxw(n + 1, 0);
        dfs(1, 0, maxw, graph, a);
        dfsReroot(1, 0, maxw, graph, result);
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

    auto res = maxWhiteSubtree(n, {0,1,1,1,0,0,0,0,1}, edges);
    for (auto r : res)
        cout << r << " ";
}