#include <vector>
#include <string>
#include <queue>
#include <iostream>
using namespace std;

bool validBfs(int n, vector<int> sequence , vector<vector<int>> edges)
{
    vector<vector<int>> graph(n + 1, vector<int>());
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }
    
    vector<int> distance(n + 1, 0);
    vector<bool> visited(n + 1, false);
    queue<int> bfs;
    
    bfs.push(sequence[0]);
    visited[sequence[0]] = true;
    distance[sequence[0]] = 1;
    
    vector<int> layer;
    int currentDistance = 1;
    int layerIndex = 1;
    auto validateLayer = [layerIndex, &layer, &sequence] ()
    {
        int nextLayerIndex = layerIndex + layer.size();
        if (nextLayerIndex > sequence.size())
            return false;
        for (int c1 : layer)
        {
            if (find(begin(sequence) + layerIndex, begin(sequence) + nextLayerIndex, c1) == end(sequence))
                return false;
        }
        return true;
    };

    while(!bfs.empty())
    {
        int n = bfs.front();
        bfs.pop();
        
        for (int c : graph[n])
        {
            if (visited[c])
                continue;
                
            visited[c] = true;
            distance[c] = distance[n] + 1;
            
            if (currentDistance < distance[c])
            {
                if (!validateLayer())
                    return false;

                // new layer
                int nextLayerIndex = layerIndex + layer.size();
                currentDistance = distance[c];
                layerIndex = nextLayerIndex;
                layer.clear();
            }

            layer.push_back(c);
            bfs.push(c);
        }
    }

    if (!validateLayer())
        return false;

    int nextLayerIndex = layerIndex + layer.size();

    return nextLayerIndex == sequence.size();
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    vector<vector<int>> edges(n - 1, vector<int>());
    for (int i = 0; i < n - 1; i++)
    {
        int e1, e2;
        cin >> e1 >> e2;

        edges[i] = { e1, e2 };
    }

    vector<int> sequence;
    for (int i = 0; i < n; i++)
    {
        int j;
        cin >> j;
        sequence.push_back(j);
    }

    cout << validBfs(n, sequence, edges);

    return 0;
}
