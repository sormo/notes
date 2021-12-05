#include <vector>
using namespace std;

void dfsTopological(int node, const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& order)
{
    visited[node] = true;
    
    for (int child : graph[node])
    {
        if (visited[child])
            continue;
        dfsTopological(child, graph, visited, order);
    }

    order.push_back(node);
}

void dfsComponents(int node, const vector<vector<int>>& graph, vector<bool>& visited)
{
    visited[node] = true;
    for (auto child : graph[node])
    {
        if (!visited[child])
            dfsComponents(child, graph, visited);
    }
}

bool solve(int n, vector<vector<int>> roads)
{
    vector<bool> visited(n, false);
    vector<vector<int>> graph(n, vector<int>());
    vector<vector<int>> graphReversed(n, vector<int>());
 
    for (const auto& e : roads)
    {
        graph[e[0]].push_back(e[1]);
        graphReversed[e[1]].push_back(e[0]);
    }

    vector<int> topologicalOrder;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
            dfsTopological(i, graph, visited, topologicalOrder);
    }
    reverse(topologicalOrder.begin(), topologicalOrder.end());
    
    visited.assign(n, false);

    int components = 0;
    for (auto node : topologicalOrder)
    {
        if (visited[node])
            continue;
        dfsComponents(node, graphReversed, visited);
        components++;
    }

    return components == 1;
}

int main()
{
    auto result = solve(2, {{0,1},
                            {1,0}});
}