#include <vector>
#include <iostream>
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

void dfsDistance(int node, int parent, const vector<vector<int>>& graph, int distance, vector<int>& distances)
{
    distances[node] = distance;
    for (int child : graph[node])
    {
        if (child != parent)
            dfsDistance(child, node, graph, distance + 1, distances);
    }
}

vector<int> countDescendants(int n, vector<vector<int>> edges, vector<vector<int>> queries)
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

    vector<int> distances(n + 1, 0);
    dfsDistance(1, 0, graph, 0, distances);

    vector<int> result;
    for (const auto& q : queries)
    {
        int node = q[0];
        int edges = q[1];

        int count = 0;
        for (int i = 1; i <= n; i++)
        {
            if (edges == distances[i])
            {
                if (inTime[node] <= inTime[i] && outTime[node] >= outTime[i])
                    count++;
            }
        }
        result.push_back(count);
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

    auto result = countDescendants(n, edges, {{1,2}, {7,2}, {4,1}, {5,5}});
}
