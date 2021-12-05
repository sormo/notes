#include<bits/stdc++.h>
using namespace std;

enum class Visited
{
    Not,
    Partially,
    Completely
};

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

bool checkPath(pair<int, int> node, const vector<pair<int, int>>& path, const vector<vector<char>>& grid)
{
    char value = grid[node.first][node.second];
    for (int i = path.size() - 1; i >= 0; i--)
    {
        if (grid[path[i].first][path[i].second] != value)
            return false;

        if (path[i] == node)
            return true;
    }

    return false;
}

bool hasSameCycle(pair<int, int> node, pair<int, int> parent, const vector<vector<char>>& grid, map<pair<int,int>, Visited>& visited, vector<pair<int, int>>& path)
{
    visited[node] = Visited::Partially;
    path.push_back(node);

    for (auto child : getChilds(node, grid))
    {
        if (child == parent)
            continue;

        if (visited[child] != Visited::Not)
        {
            if (checkPath(child, path, grid))
                return true;
        }

        if (visited[child] == Visited::Completely)
            continue;

        if (hasSameCycle(child, node, grid, visited, path))
            return true;
    }

    visited[node] = Visited::Completely;
    path.pop_back();

    return false;
}

bool containsCycle(vector<vector<char>> grid)
{
    map<pair<int,int>, Visited> visited;
    vector<pair<int, int>> path;

    return hasSameCycle({0, 0}, {-1, -1}, grid, visited, path);
}