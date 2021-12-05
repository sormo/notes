#include <vector>
using namespace std;

void dfs(int node, int parent, const vector<vector<int>>& graph, vector<vector<int>>& arr, vector<int>& depth)
{
    depth[node] = depth[parent] + 1;
    
    arr[node][0] = parent;
    for (int i = 1; i < arr[0].size(); i++)
        arr[node][i] = arr[arr[node][i-1]][i-1];
        
    for (int child : graph[node])
    {
        if (child != parent)
            dfs(child, node, graph, arr, depth);
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
    
    vector<vector<int>> arr(n + 1, vector<int>(20, 0));
    vector<int> depth(n + 1, 0);
    dfs(1, 0, graph, arr, depth);
    
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
        for (int i = arr[0].size() - 1; i >= 0 ; i--)
        {
            if ((diff >> i) & 1)
                u = arr[u][i];
        }
        
        if (u == v)
        {
            result.push_back(u);
            continue;
        }

        for (int i = arr[0].size() - 1; i >= 0; i--)
        {
            if (arr[u][i] != arr[v][i])
            {
                u = arr[u][i];
                v = arr[v][i];
            }
        }
        
        result.push_back(arr[u][0]);
    }
    
    return result;
}

int main()
{
    auto ret = LCA(5, {{1,2}, {1,3}, {3,4}, {3,5}}, {{4,5}, {2,5}, {1,4}});
}