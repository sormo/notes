#include <vector>
#include <set>
using namespace std;

vector<int> shortestPath(vector<vector<int>> roads, int n)
{
    vector<vector<pair<int, int>>> graph(n + 1, vector<pair<int, int>>());
    for (const auto& edge : roads)
    {
        graph[edge[0]].push_back({edge[1], edge[2]});
        graph[edge[1]].push_back({edge[0], edge[2]});
    }
    
    vector<int> distances(n + 1, numeric_limits<int>::max());
    vector<int> parents(n + 1, 0);
    
    // distance, src, dst
    set<pair<int, int>> currentNodes;
    currentNodes.insert({0, 1});
    
    while(!currentNodes.empty())
    {
        int node = currentNodes.begin()->second;
        int nodeDistance = currentNodes.begin()->first;
        currentNodes.erase(currentNodes.begin());

        for (const auto& child : graph[node])
        {
            int childNode = child.first;
            int edgeWeight = child.second;
            
            if (nodeDistance + edgeWeight < distances[childNode])
            {
                auto it = currentNodes.find({distances[childNode], childNode});
                if (it != currentNodes.end())
                    currentNodes.erase(it);

                currentNodes.insert({nodeDistance + edgeWeight, childNode});
                distances[childNode] = nodeDistance + edgeWeight;
                parents[childNode] = node;
            }
        }
    }
    
    vector<int> result;
    result.push_back(n);
    
    while(result.back() != 1)
        result.push_back(parents[result.back()]);
        
    reverse(begin(result), end(result));
    
    return result;
}

int main()
{
    auto resutl = shortestPath({{1,2,2}, {2,5,5}, {2,3,4}, {1,4,1}, {4,3,3}, {3,5,1}}, 5);
}