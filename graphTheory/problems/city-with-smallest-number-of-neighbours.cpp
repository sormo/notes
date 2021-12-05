#include <vector>
using namespace std;

int findTheCity(int n, vector<vector<int>> edges, int distanceThreshold)
{
    vector<vector<int>> distances(n, vector<int>(n, numeric_limits<int>::max()));
    for (const auto& e : edges)
    {
        distances[e[0]][e[1]] = e[2];
        distances[e[1]][e[0]] = e[2];
    }
    
    for (int i = 0; i < n; i++)
        distances[i][i] = 0;
        
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (distances[i][k] == numeric_limits<int>::max() || distances[k][j] == numeric_limits<int>::max())
                    continue;
                
                if (distances[i][j] > distances[i][k] + distances[k][j])
                    distances[i][j] = distances[i][k] + distances[k][j];
            }
        }
    }
    
    int resultCount = numeric_limits<int>::max();
    int resultIndex = -1;
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int k = 0; k < n; k++)
        {
            if (distances[i][k] <= distanceThreshold)
                count++;
        }
        if (count <= resultCount)
        {
            resultCount = count;
            resultIndex = i;
        }
    }

    return resultIndex;
}

int main()
{
    int result1 = findTheCity(4, {{0,1,3}, {1,2,1}, {1,3,4}, {2,3,1}}, 4);
    //int result2 = findTheCity(5, {{0,1,2},{0,4,8},{1,2,3},{1,4,2},{2,3,1},{3,4,1}}, 2);
}
