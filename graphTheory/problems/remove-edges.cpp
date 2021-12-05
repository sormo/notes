#include <vector>
#include <algorithm>
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

int maxNumEdgesToRemove(int n, vector<vector<int>> edges)
{
    int totalEdges = 0;
    vector<int> aliceParents(n+1, -1);
    for (const auto& edge : edges)
    {
        if (edge[0] == 3)
        {
            if (Find(edge[1], aliceParents) != Find(edge[2], aliceParents))
            {
                totalEdges++;
                Union(edge[1], edge[2], aliceParents);
            }
        }
    }
    
    vector<int> bobParents(aliceParents);
    
    for (const auto& edge : edges)
    {
        if (edge[0] == 1)
        {
            if (Find(edge[1], aliceParents) != Find(edge[2], aliceParents))
            {
                totalEdges++;
                Union(edge[1], edge[2], aliceParents);
            }
        }
        else if (edge[0] == 2)
        {
            if (Find(edge[1], bobParents) != Find(edge[2], bobParents))
            {
                totalEdges++;
                Union(edge[1], edge[2], bobParents);
            }
        }
    }
    
    auto checkIfConnected = [](const vector<int>& parents)
    {
        bool foundRoot = false;
        for (int i = 1; i < parents.size(); i++)
        {
            if (parents[i] == -1)
            {
                if (foundRoot)
                    return false;
                foundRoot = true;
            }
        }
        return true;
    };
    
    if (!checkIfConnected(aliceParents) || !checkIfConnected(bobParents))
        return -1;
        
    return edges.size() - totalEdges;
}

int main()
{
    auto resutl = maxNumEdgesToRemove(4, {{3,1,2}, {3,2,3}, {1,1,3}, {1,2,4}, {1,1,2}, {2,3,4}});
}