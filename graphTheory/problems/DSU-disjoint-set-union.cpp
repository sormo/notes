#include<bits/stdc++.h>
using namespace std;

int Find(int n, const vector<int>& parent)
{
    if (parent[n] == -1)
        return n;
    return Find(parent[n], parent);
}

void Union(int n1, int n2, vector<int>& parent)
{
    int p1 = Find(n1, parent);
    int p2 = Find(n2, parent);
    
    if (p1 != p2)
        parent[p2] = p1;
}

// query contains triples:
//    type, u, v
// if type == 1 -> union(u,v)
// if type == 2 -> add to the result whether u and v are in the same set
vector<bool> DSU(vector<vector<int>> query)
{
    vector<bool> result;
    vector<int> parent((int)10e5, -1);
    
    for (const auto& q : query)
    {
        if (q[0] == 1)
            Union(q[1], q[2], parent);
        else
            result.push_back(Find(q[1], parent) == Find(q[2], parent));
    }
    
    return result;
}
