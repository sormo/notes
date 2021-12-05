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

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n;

    m = n - 1;

    vector<vector<int>> edges;
    vector<vector<int>> graph(n + 1, vector<int>());

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        edges.push_back({u, v});
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<int> inTime(n + 1, 0);
    vector<int> outTime(n + 1, 0);
    int index = 0;

    dfs(5, 0, graph, inTime, outTime, index);

    for (int i = 1; i <= n; i++)
        cout << inTime[i] << " ";
    cout << "\n";
    for (int i = 1; i <= n; i++)
        cout << outTime[i] << " ";
    cout << "\n";

    vector<int> flat(n + 1, 0);
    for (int i = 1; i <= n; i++)
        flat[inTime[i]] = i;

    for (int i = 1; i <= n; i++)
        cout << flat[i] << " ";
    cout << "\n";
}
