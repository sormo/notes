#include <vector>
using namespace std;

void dfs(int node, int parent, const vector<vector<int>>& graph, vector<int>& parents, vector<int>& depth)
{
    depth[node] = depth[parent] + 1;
    parents[node] = parent;
    
    for (int child : graph[node])
    {
        if (child != parent)
            dfs(child, node, graph, parents, depth);
    }
}

vector<int> LCA(int n, vector<vector<int>> edges, vector<vector<int>> queries)
{
    vector<vector<int>> graph(n + 1, vector<int>());
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    vector<int> parents(n + 1, 0);
    vector<int> depth(n + 1, 0);
    dfs(1, 0, graph, parents, depth);

    vector<int> result;
    for (const auto& q : queries)
    {
        int u = q[0], v = q[1];

        if (u == v)
        {
            result.push_back(u);
            continue;
        }

        if (depth[u] < depth[v])
            swap(u, v);

        int diff = depth[u] - depth[v];
        for (int i = 0; i < diff; i++)
            u = parents[u];

        while (u != v)
        {
            u = parents[u];
            v = parents[v];
        }
        
        result.push_back(u);
    }
    
    return result;
}

int main()
{
    auto ret = LCA(5, {{1,2}, {1,3}, {3,4}, {3,5}}, {{4,5}, {2,5}, {1,4}});
}