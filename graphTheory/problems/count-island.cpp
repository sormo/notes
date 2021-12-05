#include <vector>
using namespace std;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1,-1, 0,  0};

int m, n;

void visit(int r, int c, vector<vector<char>>& grid)
{
    grid[r][c] = 0;
    
    for (int i = 0; i < 4; i++)
    {
        int xx = r + dx[i];
        int yy = c + dy[i];
        
        if (xx >=0 && xx < m && yy >= 0 && yy < n && grid[xx][yy] == 1)
            visit(xx, yy, grid);
    }
}

int numIslands(vector<vector<char>> grid)
{
    m = grid.size();
    n = grid[0].size();
    
    int result = 0;
    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (grid[r][c] == 0)
                continue;
            result++;
            visit(r, c, grid);
        }
    }
    return result;
}

int main()
{
    int result = numIslands({{}})
}
