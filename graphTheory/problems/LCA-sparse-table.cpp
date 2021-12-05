#include <vector>
#include <iostream>
using namespace std;

const int N = 1e5, M = 20;
vector<int> graph[N];
int sparseArray[N][M];
int depth[N];

void dfs(int node, int parent)
{
    depth[node] = depth[parent] + 1;

    sparseArray[node][0] = parent;
    for (int i = 1; i < M; i++)
        sparseArray[node][i] = sparseArray[sparseArray[node][i-1]][i-1];

    for (auto child : graph[node])
    {
        if (child != parent)
            dfs(child, node);
    }
}

int lca(int u, int v)
{
    if (u == v)
        return u;
    
    // make u lower
    if (depth[u] < depth[v])
        swap(u, v);

    int diff = depth[u] - depth[v];
    for (int i = 0; i < M; i++)
    {
        if ((diff >> i) & 1)
            u = sparseArray[u][i];
    }

    for (int j = M - 1; j >= 0; j--)
    {
        if (sparseArray[u][j] != sparseArray[v][j])
        {
            u = sparseArray[u][j];
            v = sparseArray[v][j];
        }
    }

    return sparseArray[u][0];
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n;

    m = n - 1;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;

        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // sparse array is array where rows are nodes and columns are 2^i parent of node
    dfs(1, 0);

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << sparseArray[i][j] << " ";
        cout << "\n";
    }

    auto res = lca(15, 11);
}
