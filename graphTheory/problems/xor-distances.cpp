#include <vector>
#include <iostream>
using namespace std;

void dfs(long long node, long long parent, const vector<vector<pair<long long, long long>>>& graph, vector<long long>& distances)
{
    for (const auto& childPair : graph[node])
    {
        long long child = childPair.first;
        long long weight = childPair.second;

        if (child == parent)
            continue;

        distances[child] = distances[node] ^ weight;
        dfs(child, node, graph, distances);
    }
}

long long xorDistances(int n, vector<vector<long long>> edges)
{
    const long long MOD = 1e9 + 7;

    vector<vector<pair<long long, long long>>> graph(n + 1, vector<pair<long long, long long>>());

    for (const auto& e : edges)
    {
        int u = e[0], v = e[1], w = e[2];
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    vector<long long> distances(n + 1, 0);
    dfs(1, -1, graph, distances);

    long long result = 0;
    for (int i = 0; i < 60; i++)
    {
        // iterate over all distances and count number of zeros and ones for i-th bit
        long long ones = 0, zeros = 0;
        for (int j = 1; j < distances.size(); j++)
        {
            if ((distances[j] >> i) & 1)
                ones++;
            else
                zeros++;
        }

        result += (((((long long)1 << i) % MOD * ones) % MOD) * zeros) % MOD;
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

    vector<vector<long long>> edges;

    for (int i = 0; i < m; i++)
    {
        long long u, v, w;
        cin >> u >> v;

        edges.push_back({u, v, w});
    }

    auto res = xorDistances(3, {{1,2,1}, {1,3,3}});
}