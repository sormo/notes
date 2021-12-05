#include <vector>
#include <set>
using namespace std;

int networkDelayTime(vector<vector<int>> times, int n, int k)
{
    vector<vector<pair<int, int>>> graph(n+1, vector<pair<int, int>>());
    
    for (const auto& edge : times)
        graph[edge[0]].push_back({edge[1], edge[2]});

    vector<int> distances(n + 1, numeric_limits<int>::max());

    set<pair<int, int>> nodes;
    nodes.insert({0, k});
    distances[k] = 0;

    while (!nodes.empty())
    {
        int node = nodes.begin()->second;
        int distance = nodes.begin()->first;
        nodes.erase(nodes.begin());
        
        for (const auto& child : graph[node])
        {
            int childNode = child.first;
            int childWeight = child.second;
            
            if (distance + childWeight < distances[childNode])
            {
                auto it = nodes.find({distances[childNode], childNode});
                if (it != nodes.end())
                    nodes.erase(it);
                nodes.insert({distance + childWeight, childNode});
                distances[childNode] = distance + childWeight;
            }
        }
    }
    
    // get the maximum distance
    int result = 0;
    for (int i = 1; i < distances.size(); i++)
        result = max(result, distances[i]);
        
    return result == numeric_limits<int>::max() ? -1 : result;
}

int main()
{
    int result = networkDelayTime({{2,1,1}, {2,3,1}, {3,4,1}}, 4,2); 
}
