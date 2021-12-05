#include <vector>
#include <algorithm>
#include <map>
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

bool IsConnected(const vector<int>& parents)
{
    bool parentFound = false;
    for (auto parent : parents)
    {
        if (parent == -1 && parentFound)
            return false;
        else if (parent == -1)
            parentFound = true;
    }
    return true;
}

int Mst(int nodes, const vector<vector<int>>& edges, int excludeEdge = -1, int includeEdge = -1)
{
    int result = 0;
    vector<int> parents(nodes, -1);

    if (includeEdge != -1)
    {
        Union(edges[includeEdge][0], edges[includeEdge][1], parents);
        result += edges[includeEdge][2];
    }

    for (int i = 0; i < edges.size(); i++)
    {
        if (excludeEdge == i)
            continue;

        int node1 = edges[i][0];
        int node2 = edges[i][1];
        int weight = edges[i][2];
        
        if (Find(node1, parents) != Find(node2, parents))
        {
            Union(node1, node2, parents);
            result += weight;
        }
    }

    if (!IsConnected(parents))
        return 1e5;

    return result;
}

vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> edges)
{
    vector<int> edgeIndexMapping(edges.size());
    vector<vector<int>> edgesTmp = edges;

    sort(begin(edges), end(edges), [](const auto& e1, const auto& e2) { return e1[2] < e2[2]; });

    for (int i = 0; i < edges.size(); i++)
    {
        for (int j = 0; j < edges.size(); j++)
        {
            if (edges[i] == edgesTmp[j])
                edgeIndexMapping[i] = j;
        }
    }

    int optimalWeight = Mst(n, edges);

    vector<int> critical, nonCritical;
    for (int edge = 0; edge < edges.size(); edge++)
    {
        int excludedWeight = Mst(n, edges, edge);
        if (excludedWeight > optimalWeight)
        {
            critical.push_back(edgeIndexMapping[edge]);
            continue;
        }

        int includedWeight = Mst(n, edges, -1, edge);
        if (includedWeight == optimalWeight)
            nonCritical.push_back(edgeIndexMapping[edge]);
    }

    sort(begin(critical), end(critical));
    sort(begin(nonCritical), end(nonCritical));

    return { critical, nonCritical };
}

int main()
{
    auto result = findCriticalAndPseudoCriticalEdges(6, {{0,1,1},{1,2,1},{0,2,1},{2,3,4},{3,4,2},{3,5,2},{4,5,2}});

    // [[3],[0,1,2,4,5,6]]
}
