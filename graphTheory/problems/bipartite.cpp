#include<bits/stdc++.h>
using namespace std;

enum class Visited
{
    Not,
    Red,
    Black
};

Visited Next(Visited v)
{
    return v == Visited::Red ? Visited::Black : Visited::Red;
}

bool isBipartite(int node, Visited color, const vector<vector<int>>& graph, vector<Visited>& visited)
{
    visited[node] = color;
    
    for (int child : graph[node])
    {
        if (visited[child] == Visited::Not)
        {
            if (!isBipartite(child, Next(color), graph, visited))
                return false;
        }
        else
        {
            // color of child reachable from this node has same color as this node (and it's not the parent)
            if (visited[child] == color)
                return false;
        }
    }
    
    return true;
}

bool isBipartite(vector<vector<int>> graph)
{
    vector<Visited> visited(graph.size(), Visited::Not);
    
    for (int i = 0; i < (int)graph.size(); i++)
    {
        if (visited[i] != Visited::Not)
            continue;
        
        if (!isBipartite(i, Visited::Red, graph, visited))
            return false;
    }
    
    return true;
}