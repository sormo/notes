#include <vector>
#include <map>
#include <set>
using namespace std;

vector<pair<int, int>> getChilds(pair<int, int> node, const vector<vector<char>>& grid)
{
    vector<pair<int, int>> result;

    if (node.first > 0)
        result.push_back({node.first - 1, node.second});
    if (node.second > 0)
        result.push_back({node.first, node.second - 1});
    if (node.first < grid.size() - 1)
        result.push_back({node.first + 1, node.second});
    if (node.second < grid[0].size() - 1)
        result.push_back({node.first, node.second + 1});

    return result;
}

bool checkCycle(pair<int, int> node, pair<int, int> parent, const vector<vector<char>>& grid, set<pair<int,int>>& globalVisited, set<pair<int,int>>& localVisited)
{
    globalVisited.insert(node);
    localVisited.insert(node);

    for (auto child : getChilds(node, grid))
    {
        if (child == parent || grid[child.first][child.second] != grid[node.first][node.second])
            continue;

        if (localVisited.find(child) != std::end(localVisited))
            return true;

        if (checkCycle(child, node, grid, globalVisited, localVisited))
            return true;
    }

    return false;
}

bool containsCycle(vector<vector<char>> grid)
{
    set<pair<int,int>> globalVisited;

    for (int r = 0; r < grid.size(); r++)
    {
        for (int c = 0; c < grid[r].size(); c++)
        {
            if (globalVisited.find({r, c}) != std::end(globalVisited))
                continue;
            set<pair<int,int>> localVisited;
            if (checkCycle({r, c}, {-1, -1}, grid, globalVisited, localVisited))
                return true;
        }
    }

    return false;
}

int main()
{
    vector<vector<char>> test = { {'a', 'b', 'c' },
    {'a', 'b', 'c' },
    {'a', 'b', 'c' }};

    containsCycle(test);
}
