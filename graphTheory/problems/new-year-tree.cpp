#include <vector>
#include <iostream>
#include <set>
using namespace std;

void dfs(int node, int parent, const vector<vector<int>>& graph, vector<int>& inTime, vector<int>& outTime, int& index)
{
    inTime[node] = ++index;
    for (auto child : graph[node])
    {
        if (child != parent)
            dfs(child, node, graph, inTime, outTime, index);
    }
    outTime[node] = index;
}

vector<int> solve(int n, vector<int> a, vector<vector<int>> edges, vector<vector<int>> queries)
{
    vector<vector<int>> graph(n + 1, vector<int>());
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    vector<int> inTime(n + 1, 0);
    vector<int> outTime(n + 1, 0);
    int index = 0;

    dfs(1, 0, graph, inTime, outTime, index);

    vector<int> flatten(n + 1, 0);
    for (int i = 1; i <= n; ++i)
        flatten[inTime[i]] = i;

    vector<int> result;
    for (const auto& q : queries)
    {
        int type = q[0];
        if (type == 1)
        {
            int node = q[1];
            int color = q[2];
            for (int i = inTime[node]; i <= outTime[node]; i++)
                a[flatten[i] - 1] = color;
        }
        else
        {
            int node = q[1];
            set<int> colors;
            for (int i = inTime[node]; i <= outTime[node]; i++)
                colors.insert(a[flatten[i] - 1]);
            result.push_back(colors.size());
        }
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

    auto result = solve(n, {1,1,1,1,1,1,1}, edges, {{1,3,2}, {2,1}, {1,4,3}, {2,1}, {1,2,5}, {2,1}, {1,6,4}, {2,1}, {2,2}, {2,3}});
}