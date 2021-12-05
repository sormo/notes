#include <vector>
using namespace std;

pair<int, int> Find(pair<int, int> n, vector<vector<pair<int, int>>>& parents)
{
    if (parents[n.first][n.second] == pair<int, int>( -1, -1))
        return n;
    
    // path compression
    parents[n.first][n.second] = Find(parents[n.first][n.second], parents);
    
    return parents[n.first][n.second];
}

void Union(pair<int, int> n, pair<int, int> v, vector<vector<pair<int, int>>>& parents)
{
    auto sn = Find(n, parents);
    auto sv = Find(v, parents);
    
    if (sn != sv)
        parents[sv.first][sv.second] = sn;
}

int solve(vector<vector<int>> matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    vector<vector<pair<int, int>>> parents(rows, vector<pair<int, int>>(cols, {-1, -1}));
    
    auto checkCell = [&matrix, &parents](pair<int, int> cell, pair<int, int> parent) -> pair<int, int>
    {
        if (matrix[cell.first][cell.second] == 1)
        {
            if (parent == pair<int, int>( -1, -1))
                return cell;
            else
                Union(parent, cell, parents);
        }
        return parent;
    };
    
    for (int r = 0; r < rows; r++)
    {
        pair<int, int> parent(-1, -1);
        for (int c = 0; c < cols; c++)
            parent = checkCell({r, c}, parent);
    }
    
    for (int c = 0; c < cols; c++)
    {
        pair<int, int> parent(-1, -1);
        for (int r = 0; r < rows; r++)
            parent = checkCell({r, c}, parent);
    }
    
    int result = 0;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (parents[r][c] == pair<int, int>( -1, -1) && matrix[r][c] == 1)
                result++;
        }
    }
    return result;
}

int main()
{

}