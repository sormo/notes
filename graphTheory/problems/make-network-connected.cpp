#include<bits/stdc++.h>
using namespace std;

int Find(int n, vector<int>& parents)
{
    if (parents[n] == -1)
        return n;
    parents[n] = Find(parents[n], parents);
    return parents[n];
}

bool Union(int n, int v, vector<int>& parents)
{
    int sn = Find(n, parents);
    int sv = Find(v, parents);
    
    if (sn == sv)
        return false;
        
    parents[sv] = sn;
    return true;
}

int makeConnected(int n, vector<vector<int>> connections)
{
    vector<int> parents(n, -1);
    int freeConnections = 0;
    
    for (const auto& e: connections)
    {
        if (!Union(e[0], e[1], parents))
            freeConnections++;
    }
    
    int sets = 0;    
    for (auto p : parents)
        sets += p == -1 ? 1 : 0;
        
    if (freeConnections >= sets - 1)
        return sets - 1;
    return -1;
}