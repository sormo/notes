#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <iostream>
using namespace std;

int m, n;
int dr[4] = {0,0,1,-1};
int dc[4] = {1,-1,0,0};

vector<vector<int>> highestPeak(vector<vector<int>> isWater)
{
    m = isWater.size();
    n = isWater[0].size();
    
    vector<vector<int>> distances(m, vector<int>(n, INT_MAX));
    queue<pair<int, int>> Q;
    
    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < n; c++)
        {
            if (isWater[r][c])
            {
                distances[r][c] = 0;
                Q.push({r,c});
            }
        }
    }
    
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
                distances[rr][cc] = min(distances[rr][cc], distances[r][c] + 1);
                Q.push({rr, cc});
            }
        }
    }

    // for (int r = 0; r < m; r++)
    // {
    //     for (int c = 0; c < n; c++)
    //     {
    //         cout << distances[r][c] << " ";
    //     }
    //     cout << "\n";
    // }

    return distances;
}

int main()
{
    auto res1 = highestPeak({{1,1,1,1},
                             {1,0,0,0},
                             {1,0,0,0},
                             {1,0,0,0}});
}