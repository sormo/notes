#include <vector>
#include <map>
using namespace std;

vector<int> countPairs(int n, vector<vector<int>> edges, vector<int> queries)
{
    vector<int> degree(n + 1, 0);
    map<pair<int, int>, int> m;
    
    for (const auto& e : edges)
    {
        degree[e[0]]++;
        degree[e[1]]++;
        
        if (auto it = m.find({e[0],e[1]}) == end(m))
        {
            m[{e[0],e[1]}] = 1;
            m[{e[1],e[0]}] = 1;
        }
        else
        {
            m[{e[0],e[1]}]++;
            m[{e[1],e[0]}]++;
        }
    }
    
    vector<int> res(edges.size() + 1, 0);
    for (int b = 2; b <= n; b++)
    {
        for (int a = 1; a < b; a++)
        {
            int inc = degree[a] + degree[b] - m[{a,b}];
            res[inc]++;
        }
    }
    
    vector<int> result;
    for (auto q : queries)
    {
        int r = 0;
        for (int i = q + 1; i < res.size(); i++)
            r += res[i];
        result.push_back(r);
    }
    
    return result;
}

int main()
{
    auto res = countPairs(4, {{1,2},{2,4},{1,3},{2,3},{2,1}}, {2,3});
}