#include <vector>
#include <set>
using namespace std;

int Find(int node, vector<int>& parents)
{
    if (parents[node] == -1)
        return node;
    parents[node] = Find(parents[node], parents);
    return parents[node];
}

void Union(int n, int v, vector<int>& parents)
{
    int sn = Find(n, parents);
    int sv = Find(v, parents);

    if (sn != sv)
        parents[sv] = sn;
}

bool verifyDiff(int diff, int nodes, const vector<vector<int>>& edges, const vector<int>& values, int start, int end)
{
    vector<int> parents(nodes + 1, -1);

    for (const auto& e : edges)
    {
        if (abs(values[e[0]] - values[e[1]]) <= diff)
            Union(e[0], e[1], parents);
    }

    return Find(start, parents) == Find(end, parents); 
}

int specialPath(int n, vector<int> a, vector<vector<int>> edges, int start, int end)
{
    set<int> differencesSet;
    for (const auto& e : edges)
        differencesSet.insert(abs(a[e[0]] - a[e[1]]));

    for (auto d : differencesSet)
    {
        if (verifyDiff(d, n, edges, a, start, end))
            return d;
    }

    return -1;
}

int main()
{
    int result = specialPath(7, { 56, 32, 67, 29, 16, 6, 64 }, {{5,3}, {4, 5}, {5, 1}, {5, 2}}, 1, 2);

    return 0;
}