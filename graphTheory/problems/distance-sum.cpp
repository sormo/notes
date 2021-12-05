#include <vector>
#include <iostream>
using namespace std;

void dfs(int node, int parent, int distance, vector<int>& distances, vector<int>& distancesSum, const vector<vector<int>>& graph)
{
    distances[node] = distance;

    for (auto child : graph[node])
    {
        if (child != parent)
        {
            dfs(child, node, distance + 1, distances, distancesSum, graph);
            distancesSum[node] += distancesSum[child];
        }
    }

    distancesSum[node] += distances[node];
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

    // distances to nodes from root node
    vector<int> distances(n + 1, 0);
    // sum of distances to node
    vector<int> distancesSum(n + 1, 0);
    dfs(1, 0, 0, distances, distancesSum, graph);

    // brute-force
    vector<int> result;
    for (int i = 1; i <= n; i++)
    {
        vector<int> distances(n + 1, 0);
        vector<int> distancesSum(n + 1, 0);
        dfs(i, 0, 0, distances, distancesSum, graph);
        result.push_back(distancesSum[i]);
    }
}