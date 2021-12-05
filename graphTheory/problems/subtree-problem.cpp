#include <vector>
using namespace std;

void dfs(int node, int parent, const vector<vector<int>>& graph, vector<int>& counts)
{
    int count = 1;
    for (int child : graph[node])
    {
        if (child == parent)
            continue;
        dfs(child, node, graph, counts);
        count += counts[child];
    }
    counts[node] = count;
}

vector<int> subtreeProblem (int n, vector<vector<int>> edges, vector<int> queries)
{
    vector<vector<int>> graph(n + 1, vector<int>());
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }
    
    vector<int> counts(n, 0);
    dfs(1, 0, graph, counts);
    
    vector<int> result;
    for (auto q : queries)
        result.push_back(counts[q]);
    
    return result;
}

int main()
{
    auto result = subtreeProblem(5, {{1,2}, {1,3}, {3,4}, {3,5}}, {1,2,3,4,5});
}