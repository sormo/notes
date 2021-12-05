#include <vector>
using namespace std;

void dfs(int node, int parent, vector<int>& values, const vector<vector<pair<int, int>>>& graph, const vector<bool>& excluded)
{
    for (const auto& child : graph[node])
    {
        if (child.first == parent)
            continue;
        if (excluded[child.first])
            continue;
        values[child.first] = values[node] + child.second;
        dfs(child.first, node, values, graph, excluded);
    }
}

struct LongestPath
{
    int node1 = 0;
    int node2 = 0;
    long long value = 0;
};

LongestPath findLongestPath(const vector<vector<pair<int, int>>>& graph, const vector<bool>& excluded)
{
    int root = 1;
    while(excluded[root])
        root++;
    vector<int> values(graph.size(), 0);
    dfs(root, 0, values, graph, excluded);

    LongestPath path;
    auto SetMaxValue = [&values](int& node, long long& value)
    {
        for (int i = 1; i < values.size(); i++)
        {
            if (values[i] > value)
            {
                node = i;
                value = values[i];
            }
        }
    };

    SetMaxValue(path.node1, path.value);

    values = vector<int>(graph.size(), 0);
    dfs(path.node1, 0, values, graph, excluded);

    path.value = 0;
    SetMaxValue(path.node2, path.value);

    return path;
}

long long holi(int n, vector<vector<int>> edges)
{
    vector<vector<pair<int, int>>> graph(n+1, vector<pair<int, int>>());
    for (const auto& e : edges)
    {
        graph[e[0]].push_back({e[1], e[2]});
        graph[e[1]].push_back({e[0], e[2]});
    }

    long long result = 0;
    vector<bool> excluded(n+1, false);
    // n / 2 paths will be found
    for (int i = 0; i < n/2; i++)
    {
        auto path = findLongestPath(graph, excluded);
        result += 2 * path.value;
        excluded[path.node1] = true;
        excluded[path.node2] = true;
    }

    return result;
}

int main()
{
    auto ret = holi(6, {{1,2,3}, {2,3,4}, {2,4,1}, {4,5,8}, {5,6,5}});
}
