#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool dfs(int node, const vector<vector<int>>& graph, const string& colors, vector<bool>& visited, vector<int>& colorCounts, int& result)
{
    if (visited[node])
        return false;
    
    visited[node] = true;
    colorCounts[colors[node] - 'a']++;
    result = max(result, colorCounts[colors[node] - 'a']);

    for (int child : graph[node])
    {
        if (!dfs(child, graph, colors, visited, colorCounts, result))
            return false;
    }

    visited[node] = false;
    colorCounts[colors[node] - 'a']--;
    
    return true;
}

int largestPathValue(string colors, vector<vector<int>> edges)
{
    vector<vector<int>> graph(colors.size(), vector<int>());
    
    for (const auto& e : edges)
        graph[e[0]].push_back(e[1]);
        
    vector<int> colorCounts('z' - 'a', 0);
    
    int result = -1;
    vector<bool> visited(colors.size(), false);

    vector<int> indegree(colors.size(), 0);
    for (const auto& e : edges)
        indegree[e[1]]++;

    // iterate over paths with dfs
    // with backtrack from leaf node check the colors

    for (int i = 0; i < colors.size(); i++)
    {
        // start dfs only from root nodes
        if (indegree[i] != 0)
            continue;

        if (!dfs(i, graph, colors, visited, colorCounts, result))
            return -1;
    }
    
    return result;
}

int main()
{
    int result = largestPathValue("abaca", {{0,1},{0,2},{2,3},{3,4}});

    return result;
}
