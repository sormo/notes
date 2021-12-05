#include<bits/stdc++.h>
using namespace std;

enum class Visited
{
    Not,
    Partially,
    Completely
};

bool hasOddLengthCycle(int node, int parent, const vector<vector<int>>& graph, vector<Visited>& visited, int count)
{
    visited[node] = Visited::Partially;
    
    for (int child : graph[node])
    {
        if (child == parent)
            continue;
        
        if (visited[node] != Visited::Not)
        {
            if (count % 2 == 0)
                return true;
        }
        
        if (visited[node] != Visited::Completely)
        {
            if (hasOddLengthCycle(child, node, graph, visited, count + 1))
                return true;
        }
    }
    
    visited[node] = Visited::Completely;
    
    return false;
}

bool solve(vector<vector<int>> graph)
{
    vector<Visited> visited(graph.size(), Visited::Not);
    
    for (int i = 0; i < graph.size(); i++)
    {
        if (visited[i] == Visited::Completely)
            continue;

        if (hasOddLengthCycle(i, -1, graph, visited, 1))
            return true;
    }
    
    return false;
}
