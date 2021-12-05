#include<bits/stdc++.h>
using namespace std;

int Find(int node, vector<int>& parents)
{
    if (parents[node] == -1)
        return node;
    parents[node] = Find(parents[node], parents);
    return parents[node];
}

void Union(int p1, int p2, vector<int>& parents)
{
    int v1 = Find(p1, parents);
    int v2 = Find(p2, parents);
    
    if (v1 != v2)
    {
        parents[v2] = v1;
    }
}

int distance(const vector<int>& p1, const vector<int>& p2)
{
    return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]);
}

int minCostConnectPoints(vector<vector<int>> points)
{
    vector<pair<int, pair<int, int>>> edges;
    
    for (size_t i = 0; i < points.size(); i++)
    {
        for (size_t j = i+1; j < points.size(); j++)
        {
            edges.push_back({ distance(points[i], points[j]), {i, j} });
        }
    }
    
    sort(begin(edges), end(edges));
    
    vector<int> parents(points.size(), -1);
    int result = 0;
    
    for (const auto& edge : edges)
    {
        int node1 = edge.second.first;
        int node2 = edge.second.second;
        int weight = edge.first;
        
        if (Find(node1, parents) == Find(node2, parents))
            continue;
        
        result += weight;
        Union(node1, node2, parents);
    }
    
    return result;
}
