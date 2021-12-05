#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

int m, n;
int dr[] = {0,0,1,-1};
int dc[] = {1,-1,0,0};

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

    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < n; c++)
        {
            auto it = find(begin(nodes), end(nodes), pair<int, int>{r, c});
            if (it != end(nodes) )
            {
                for (int rr = 0; rr < m; rr++)
                {
                    for (int cc = 0; cc < n; cc++)
                    {
                        distances[rr][cc] = min(distances[rr][cc], distance(rr, cc, r, c));
                    }
                }
            }
            else if (grid[r][c] == 1)
            {
                distances[r][c] = 0;
            }
        }
    }

    int result = INT_MAX;
    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < n; c++)
        {
            // cout << distances[r][c] << " ";

            if (grid[r][c] != 0)
                continue;

            for (int i = 0; i < 4; i++)
            {
                int rr = r + dr[i];
                int cc = c + dc[i];

                auto it = find(begin(nodes), end(nodes), pair<int, int>{rr, cc});
                if (it != end(nodes))
                    continue;

                if (rr >= 0 && rr < m && c >= 0 && c < n && grid[rr][cc] == 1)
                {
                    result = min(result, distances[r][c]);
                    break;
                }
            }
        }
        // cout << "\n";
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
