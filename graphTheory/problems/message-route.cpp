#include<bits/stdc++.h>
using namespace std;

int messageRoute(int n, vector<vector<int>> edges)
{
    map<int, vector<int>> graph;
    auto addEdge = [&graph] (int e1, int e2)
    {
        if (graph.find(e1) == graph.end())
            graph[e1] = { e2 };
        else
            graph[e1].push_back(e2);
    };
    
    for (const auto& e: edges)
    {
        addEdge(e[0], e[1]);
        addEdge(e[1], e[0]);
    }
    
    queue<int> q;
    vector<bool> visited(n + 1, false);
    vector<int> distance(n + 1, -1);
    
    q.push(1);
    visited[1] = true;
    distance[1] = 1;
    
    while(!q.empty())
    {
        int n = q.front();
        q.pop();
        
        for (const auto e : graph[n])
        {
            if (visited[e])
                continue;
            distance[e] = distance[n] + 1;
            visited[e] = true;
            q.push(e);
        }
    }
    
    return distance[n];
}