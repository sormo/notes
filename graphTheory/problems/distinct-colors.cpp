#include <vector>
#include <set>
using namespace std;

void dfs(int node, int parent, const vector<vector<int>>& graph, vector<int>& inTime, vector<int>& outTime, int& time)
{
    time++;
    inTime[node] = time;

    for (auto child : graph[node])
    {
        if (child == parent)
            continue;
        dfs(child, node, graph, inTime, outTime, time);
    }

    outTime[node] = time;
}

vector<int> solve(int n, vector<int> a, vector<vector<int>> edges)
{
    vector<int> inTime(n + 1, 0);
    vector<int> outTime(n + 1, 0);

    vector<vector<int>> graph(n + 1, vector<int>());
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    int time = 0;
    dfs(1, 0, graph, inTime, outTime, time);

    vector<int> result(n, 0);
    for (int i = 1; i <= n; i++)
    {
        set<int> colors;
        for (int j = inTime[i]; j <= outTime[i]; j++)
        {
            colors.insert(a[j - 1]);
        }
        result[i - 1] = colors.size();
    }
    return result;
}

int main()
{
    auto ret = solve(5, {2,3,2,2,1}, {{1,2}, {1,3}, {3,4}, {3,5}});
}
