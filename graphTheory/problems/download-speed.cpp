#include <vector>
#include <iostream>
#include <queue>
using namespace std;

struct Dinic
{
    Dinic(int source, int sink, int nodeCount)
        : source(source), sink(sink)
    {
        graph.resize(nodeCount);
    }

    void AddEdge(int from, int to, long long flow)
    {
        // residual capacity
        edges.push_back({from, to, flow});
        graph[from].push_back(edges.size() - 1);
        // actual flow
        edges.push_back({to, from, 0});
        graph[to].push_back(edges.size() - 1);
    }

    long long MaximumFlow()
    {
        long long result = 0;
        while(CreateLevelGraph())
        {
            // augment using augmenting path while possible
            while(long long flow = Augment())
            {
                result += flow;
            }
        }
        return result;
    }

private:
    bool CreateLevelGraph()
    {
        levels.clear();
        levels.resize(graph.size(), -1);

        queue<int> Q;
        Q.push(source);
        levels[source] = 0;

        // perform BFS storing distance to source
        // (use levels also as visited array)
        // (do not use edge which has 0 flow)

        while(!Q.empty())
        {
            int node = Q.front();
            Q.pop();

            for (auto edgeIndex : graph[node])
            {
                int child = edges[edgeIndex].to;
                long long flow = edges[edgeIndex].flow;

                if (flow != 0 && levels[child] == -1)
                {
                    levels[child] = levels[node] + 1;
                    Q.push(child);
                }
            }
        }

        return levels[sink] != -1;
    }

    long long Augment()
    {
        vector<bool> visited(graph.size(), false);

        return AugmentDfs(source, 1e9 + 1, visited);
    }

    long long AugmentDfs(int node, long long flow, vector<bool>& visited)
    {
        if (node == sink)
            return flow;

        for (auto edgeIndex : graph[node])
        {
            int child = edges[edgeIndex].to;
            long long childFlow = edges[edgeIndex].flow;

            if (visited[child])
                continue;

            // important thing here is that we are allowed to move only up the level
            if (levels[node] + 1 != levels[child])
                continue;

            long long bottleneck = AugmentDfs(child, min(flow, childFlow), visited);
            if (bottleneck != 0)
            {
                // found augmenting path, augment the flows in edges
                edges[edgeIndex].flow -= bottleneck;
                edges[edgeIndex ^ 1].flow += bottleneck;

                // xor 1 above means -1 for even and +1 for odd values

                return bottleneck;
            }
        }

        return 0;
    }

    struct Edge
    {
        int from;
        int to;
        long long flow;
    };

    int source;
    int sink;
    vector<vector<int>> graph;
    vector<Edge> edges;
    vector<int> levels;
};

long long solve(int n, vector<vector<int>> edges)
{
    Dinic dinic(1, n, n + 1);

    for (const auto& e : edges)
        dinic.AddEdge(e[0], e[1], e[2]);
    
    return dinic.MaximumFlow();
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, e;
    cin >> n >> e;

    vector<vector<int>> edges;
    for (int i = 0; i < e; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;

        edges.push_back({u,v,w});
    }

    cout << solve(n, edges);
}