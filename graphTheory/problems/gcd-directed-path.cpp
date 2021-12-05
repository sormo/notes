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

int gcd(int a, int b)
{
    return (a == 0) ? b : gcd(b % a, a);
}

void dfsComponents(int node, const vector<vector<int>>& graph, vector<bool>& visited, vector<int>& costs, int& cost)
{
    visited[node] = true;
    for (auto child : graph[node])
    {
        if (visited[child])
            continue;
        dfsComponents(child, graph, visited, costs, cost);
    }
    if (cost == INT_MAX)
        cost = costs[node];
    else
        cost = min(costs[node], gcd(costs[node], cost));
}

int solve(int n, vector<int> c, vector<vector<int>> edges)
{
    vector<bool> visited(n + 1, false);
    vector<vector<int>> graph(n + 1, vector<int>());
    vector<vector<int>> graphReversed(n + 1, vector<int>());
 
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graphReversed[e[1]].push_back(e[0]);
    }

    vector<int> topologicalOrder;
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
            dfsTopological(i, graph, visited, topologicalOrder);
    }
    reverse(topologicalOrder.begin(), topologicalOrder.end());
    
    visited.assign(n + 1, false);

    vector<int> costs;
    for (auto node : topologicalOrder)
    {
        if (visited[node])
            continue;
        int cost = INT_MAX;
        dfsComponents(node, graphReversed, visited, c, cost);
        costs.push_back(cost);
    }

    int result = INT_MAX;
    for (auto cost : costs)
    {
        if (result == INT_MAX)
            result = cost;
        else
            result = min(result, gcd(cost, result));
        //result = min(result, cost);
    }
    return result;
}

int main()
{
    auto result = solve(3, {4,6,8}, {{1,2},
                            {2,3}});
}