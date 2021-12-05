#include <vector>
using namespace std;

void dfs(int node, int parent, const vector<vector<int>>& graph, int count, int& result)
{
    result = max(result, count);
    
    for (int child : graph[node])
    {
        if (child != parent)
            dfs(child, node, graph, count + 1, result);
    }
}

int treeDiameter(vector<vector<int>> edges)
{
    int n = edges.size() + 1;
    
    vector<vector<int>> graph(n + 1, vector<int>());
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }
    
    int result = 0;
    for (int i = 1; i <= n; i++)
    {
        if (graph[i].size() == 1)
        {
            dfs(i, 0, graph, 1, result);
        }
    }
    
    return result - 1;
}

// 

void dfs2(int node, int parent, const vector<vector<int>>& graph, int count, int& maxCount, int& maxNode)
{
    if (count > maxCount)
    {
        maxCount = count;
        maxNode = node;
    }
    
    for (int child : graph[node])
    {
        if (child != parent)
            dfs2(child, node, graph, count + 1, maxCount, maxNode);
    }
}

int treeDiameter2(vector<vector<int>> edges)
{
    int n = edges.size() + 1;
    
    vector<vector<int>> graph(n + 1, vector<int>());
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }
    
    int maxCount = 0;
    int maxNode1 = 0;
    dfs2(1, 0, graph, 0, maxCount, maxNode1);
    
    maxCount = 0;
    int maxNode2 = 0;
    dfs2(maxNode1, 0, graph, 0, maxCount, maxNode2);

    return maxCount;
}
