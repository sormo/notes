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

long long distance(const vector<long long>& p1, const vector<long long>& p2)
{
    return min(abs(p1[0] - p2[0]), abs(p1[0] - p1[1]));
}

long long buildRoads(vector<vector<long long>> nodes)
{
    vector<pair<long long, pair<int, int>>> edges;
    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = i + 1; j < nodes.size(); j++)
            edges.push_back({distance(nodes[i], nodes[j]), {i, j}});
    }
    
    sort(begin(edges), end(edges));
    
    vector<int> parents(nodes.size(), -1);
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

int main()
{
    auto result = buildRoads({{8,3}, {4,9}, {12,19}, {18,1}, {13,5}, {7,6}});
}
