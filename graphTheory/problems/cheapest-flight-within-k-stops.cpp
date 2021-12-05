#include<bits/stdc++.h>
using namespace std;

// modified Bellman Ford with temp array
// updates are done in temp array to get distances in bfs manner (first iteration 
// get distances only one stop from source and so on)

int findCheapestPrice(int n, vector<vector<int>> flights, int src, int dst, int k)
{
    vector<int> distances(n + 1, numeric_limits<int>::max());
    distances[src] = 0;
    
    for (int i = 0; i <= k; i++)
    {
        vector<int> distancesTemp(distances);
        for (const auto& flight : flights)
        {
            if (distances[flight[0]] == numeric_limits<int>::max())
                continue;
                
            if (distances[flight[0]] + flight[2] < distances[flight[1]])
                distancesTemp[flight[1]] = distances[flight[0]] + flight[2];
        }
        distances = distancesTemp;
    }
    
    return distances[dst] == numeric_limits<int>::max() ? -1 : distances[dst];
}