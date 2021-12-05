#include <vector>
using namespace std;

void dfs(int node, int parent, vector<vector<int>>& graph, vector<bool>& vis, vector<int>& disc, vector<int>& low, int& index, vector<vector<int>>& result)
{
    vis[node] = true;
    disc[node] = low[node] = index++;
    
    for (auto child : graph[node])
    {
        if (!vis[child])
        {
            dfs(child, node, graph, vis, disc, low, index, result);
            low[node] = min(low[node], low[child]);
            
            if (low[child] > disc[node])
                result.push_back({node, child});
        }
        else if (child != parent)
        {
            low[node] = min(low[node], disc[child]);
        }
    }
}

vector<vector<int>> criticalConnections(int n, vector<vector<int>> connections)
{
    vector<vector<int>> graph(n, vector<int>());
    
    for (const auto& e: connections)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }
    
    vector vis(n, false);
    vector disc(n, -1);
    vector low(n, -1);
    int index = 1;
    
    vector<vector<int>> result;
    dfs(0, -1, graph, vis, disc, low, index, result);
    
    return result;
}

int main()
{
    auto result = criticalConnections(4, {{0,1}, {1,2}, {2,0}, {1,3}});
}