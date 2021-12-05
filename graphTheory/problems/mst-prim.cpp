#include<bits/stdc++.h>
using namespace std;

int MST(int n, vector<vector<int>> edges)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;
    vector<bool> visited(n + 1, false);
    
    vector<vector<pair<int, int>>> graph(n + 1, vector<pair<int, int>>());
    for (const auto& edge : edges)
    {
        graph[edge[0]].push_back({edge[1], edge[2]});
        graph[edge[1]].push_back({edge[0], edge[2]});
    }
    
    queue.push({0, 1});
    
    int result = 0;
    while(!queue.empty())
    {
        auto weight = queue.top().first;
        auto node = queue.top().second;
        queue.pop();
        
        if (visited[node])
            continue;
        visited[node] = true;
        
        result += weight;
        
        for (const auto& child : graph[node])
            queue.push({child.second, child.first});
    }
    
    return result;
}
