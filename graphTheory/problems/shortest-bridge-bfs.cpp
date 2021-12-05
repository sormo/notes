#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

int m, n;
int dr[4] = {0,0,1,-1};
int dc[4] = {1,-1,0,0};

int distance(int r1, int c1, int r2, int c2)
{
    return abs(r1 - r2) + abs(c1 - c2);
}

void dfs(int r, int c, const vector<vector<int>>& grid, vector<vector<bool>>& visited, vector<pair<int, int>>& result)
{
    result.push_back({r, c});
    visited[r][c] = true;

    for (int i = 0; i < 4; i++)
    {
        int rr = r + dr[i];
        int cc = c + dc[i];

        if (rr >= 0 && rr < m && c >= 0 && c < n && grid[rr][cc] == 1 && !visited[rr][cc])
            dfs(rr, cc, grid, visited, result);
    }
}

vector<pair<int, int>> getNodesOfSingleIsland(const vector<vector<int>>& grid)
{
    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (grid[r][c] == 1)
            {
                vector<pair<int, int>> result;
                vector<vector<bool>> visited(m, vector<bool>(n, false));
                dfs(r, c, grid, visited, result);
                return result;
            }
        }
    }
    return {};
}

int shortestBridge(vector<vector<int>> grid)
{
    m = grid.size();
    n = grid[0].size();

    vector<vector<int>> distances(m, vector<int>(n, INT_MAX));
    auto nodes = getNodesOfSingleIsland(grid);
    queue<pair<int, int>> Q;

    for (auto node : nodes)
    {
        distances[node.first][node.second] = 0;
        Q.push(node);
    }

    int result = INT_MAX;
    while(!Q.empty())
    {
        int r = Q.front().first;
        int c = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++)
        {
            int rr = r + dr[i];
            int cc = c + dc[i];

            if (rr >= 0 && rr < m && cc >=0 && cc < n && distances[rr][cc] == INT_MAX)
            {
                if (grid[rr][cc] == 1)
                {
                    result = min(result, distances[r][c]);
                }
                else
                {
                    distances[rr][cc] = distances[r][c] + 1;
                    Q.push({rr, cc});
                }
            }
        }
    }

    return result;
}

int main()
{
    int res1 = shortestBridge({{1,1,1,1,1},
                              {1,0,0,0,1},
                              {1,0,1,0,1},
                              {1,0,0,0,1},
                              {1,1,1,1,1}});

    int res2 = shortestBridge({{0,1,0},
                               {0,0,0},
                               {0,0,1}});
    
    int res3 = shortestBridge({{0,1},
                               {1,0}});
}
