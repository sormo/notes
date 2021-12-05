#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void dfs(int node, int parent, vector<vector<pair<int, int>>>& graph, int& value)
{
    for (int i = 0; i < graph[node].size(); i++)
    {
        int child = graph[node][i].first;
        int weight = graph[node][i].second;
        if (child != parent)
        {
            value += weight;
            graph[node][i].second = 0;
            dfs(child, node, graph, value);
        }
    }
}

vector<int> choosingCapital(int n, vector<vector<int>> edges)
{
    vector<vector<pair<int, int>>> graph(n + 1, vector<pair<int, int>>());

    for (const auto& e : edges)
    {
        graph[e[0]].push_back({e[1], 0});
        graph[e[1]].push_back({e[0], 1});
    }

    vector<int> result;
    int minWeight = numeric_limits<int>::max();
    for (int i = 1; i <= n; i++)
    {
        auto tmpGraph(graph);
        int weight = 0;
        dfs(i, 0, tmpGraph, weight);
        if (weight <= minWeight)
        {
            if (weight < minWeight)
            {
                minWeight = weight;
                result.clear();
            }
            result.push_back(i);
        }
    }

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
}