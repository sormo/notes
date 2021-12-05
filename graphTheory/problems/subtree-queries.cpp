#include <vector>
#include <iostream>
using namespace std;

void dfs(int node, int parent, const vector<vector<int>>& graph, vector<int>& inTime, vector<int>& outTime, int& index)
{
    inTime[node] = ++index;
    for (auto child : graph[node])
    {
        if (child != parent)
            dfs(child, node, graph, inTime, outTime, index);
    }
    outTime[node] = index;
}

vector<int> subtreeQuery(int n, vector<int> a, vector<vector<int>> edges, vector<vector<int>> queries)
{
    vector<vector<int>> graph(n + 1, vector<int>());
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    vector<int> inTime(n + 1, 0);
    vector<int> outTime(n + 1, 0);
    int index = 0;

    dfs(1, 0, graph, inTime, outTime, index);

    vector<int> flat(n + 1, 0);
    for (int i = 1; i <= n; i++)
        flat[inTime[i]] = i;

    vector<int> result;
    for (auto q : queries)
    {
        if (q[0] == 1)
        {
            a[q[1] - 1] = q[2];
        }
        else
        {
            int res = 0;
            for (int i = inTime[q[1]]; i <= outTime[q[1]]; i++)
                res += a[flat[i] - 1];
            result.push_back(res);
        }
    }

    return result;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n;

    m = n - 1;

    vector<vector<int>> edges;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        edges.push_back({u, v});
    }

    auto result = subtreeQuery(n, {4, 2, 5, 2, 1}, edges, { {2, 3}, {1,5,3}, {2,3}});
    for (int i = 1; i <= n; i++)
        cout << result[i] << " ";
    cout << "\n";
}
