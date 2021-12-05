#include <vector>
using namespace std;

int Find(int n, const vector<int>& parents)
{
    if (parents[n] == -1)
        return n;
    return Find(parents[n], parents);
}

void Union(int n, int v, vector<int>& parents)
{
    int sn = Find(n, parents);
    int sv = Find(v, parents);
    
    if (sn != sv)
        parents[sv] = sn;
}

bool solve(vector<vector<int>> edges)
{
    vector<int> parents(edges.size() + 1, -1);
    
    for (const auto& e : edges)
    {
        if (Find(e[0], parents) == Find(e[1], parents))
            return false;
        
        Union(e[0], e[1], parents);
    }
    
    return true;
}

int main()
{
    bool result = solve({ {0, 1}, {0, 2}, {3, 4}, {4, 5} });

    return 0;
}