#include <vector>
using namespace std;

int dfs(int node, const vector<vector<int>>& graph)
{
    int result = 0;
    
    if (node == graph.size() - 1)
        result = (result + 1) % ((int)10e9 + 7);
        
    for (int child : graph[node])
        result = (result + dfs(child, graph)) % ((int)10e9 + 7);
    
    return result;
}

int gameRoutes(int n, vector<vector<int>> edges)
{
    vector<vector<int>> graph(n+1, vector<int>());
    for (const auto& e : edges)
        graph[e[0]].push_back(e[1]);
        
    return dfs(1, graph);
}

int main()
{
    int result = gameRoutes(5, {{1,2}, {1,3}, {2, 3}, {1,4}, {1,5}});

    return result;
}