#include <vector>
#include <set>
#include <iostream>
using namespace std;

int n;
int dr[] = {1,-1,0,0};
int dc[] = {0,0,1,-1};

// color 0 is always zero
int colors[501];
bool visited[501][501];

void visit(int r, int c, vector<vector<int>>& grid, int color)
{
    grid[r][c] = color;
    colors[color]++;
    visited[r][c] = true;
    
    for (int i = 0; i < 4; i++)
    {
        int rr = r + dr[i];
        int cc = c + dc[i];
        
        if (rr >= 0 && rr < n && cc >= 0 && cc < n && grid[rr][cc] == 1 && !visited[rr][cc])
            visit(rr, cc, grid, color);
    }
}

int largestIsland(vector<vector<int>> grid)
{
    n = grid.size();
    
    int numberOfComponents = 0;
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (grid[r][c] == 1 && !visited[r][c])
                visit(r, c, grid, ++numberOfComponents); // first component is 1
        }
    }
    
    // for (int r = 0; r < n; r++)
    // {
    //     for (int c = 0; c < n; c++)
    //     {
    //         cout << grid[r][c] << " ";
    //     }
    //     cout << "\n";
    // }

    int result = 0;
    for (int i = 1; i <= numberOfComponents; i++)
        result = max(result, colors[i]);
    
    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (grid[r][c] == 0)
            {
                set<int> differentColors;
                for (int i = 0; i < 4; i++)
                {
                    int rr = r + dr[i];
                    int cc = c + dc[i];
       
                    if (rr >= 0 && rr < n && cc >= 0 && cc < n)
                    {
                        // doesnt matter if we insert water
                        differentColors.insert(grid[rr][cc]);
                    }
                }
                
                int ans = 1;
                for (auto c : differentColors)
                    ans += colors[c];
                    
                result = max(result, ans);
            }
        }
    }
    
    return result;
}

int main()
{
    int result = largestIsland({{0,1,1},
                                {1,0,1},
                                {0,1,0}});
}