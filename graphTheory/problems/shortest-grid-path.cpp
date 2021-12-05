#include <vector>
#include <map>
#include <set>
#include <limits>
using namespace std;

pair<int, int> childs[] = 
{
    {-1, 0},
    { 1, 0},
    { 0,-1},
    { 0, 1}
};

int shortest_path(vector<vector<int>> grid)
{
    map<pair<int, int>, int> distances;
    
    // weight, dst[row], dst[col]
    set<vector<int>> nodes;
    nodes.insert({ grid[0][0], 0, 0 });
    distances[{0,0}] = grid[0][0];
    
    while(!nodes.empty())
    {
        pair<int, int> node(nodes.begin()->at(1), nodes.begin()->at(2));
        int distance = nodes.begin()->at(0);
        nodes.erase(nodes.begin());
        
        for (const auto& childVal : childs)
        {
            pair<int, int> child = { node.first + childVal.first, node.second + childVal.second };
            if (child.first < 0 || child.first >= grid.size() || child.second < 0 || child.second >= grid[0].size())
                continue;
            int childWeight = grid[child.first][child.second];
            
            int childDist = numeric_limits<int>::max();
            auto it = distances.find(child);
            if (it != distances.end())
                childDist = it->second;
                
            if (childDist > distance + childWeight)
            {
                auto nodesIt = nodes.find({childDist, child.first, child.second});
                if (nodesIt != nodes.end())
                    nodes.erase(nodesIt);
                nodes.insert({distance + childWeight, child.first, child.second});

                distances[child] = distance + childWeight;
            }
        }
    }
    
    return distances[{grid.size() - 1, grid[0].size() - 1}];
}

int main()
{
    vector<vector<int>> grid = { {  31, 100,  65,  12,  18 },
                                 {  10,  13,  47, 157,   6 },
                                 { 100, 113, 174,  11,  33 },
                                 {  88, 124,  41,  20, 140 },
                                 {  99,  32, 111,  42,  20 }};

    int result = shortest_path(grid);
}
