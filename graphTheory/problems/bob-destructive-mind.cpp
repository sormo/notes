#include <vector>
#include <set>
#include <iostream>
using namespace std;

int N = 1e5;

vector<vector<int>> graph(N, vector<int>());
vector<int> discoveryTime(N, 0);
vector<int> lowTime(N, 0);
vector<bool> visited(N, false);
set<int> articulationPoints;
int discoveryIndex = 1;

void dfs(int node, int parent)
{
    visited[node] = true;
    discoveryTime[node] = lowTime[node] = discoveryIndex++;

    int childCount = 0;
    for (int child : graph[node])
    {
        if (!visited[child])
        {
            dfs(child, node);
            lowTime[node] = min(lowTime[node], lowTime[child]);
            childCount++;

            if (parent != 0 && lowTime[child] >= discoveryTime[node])
                articulationPoints.insert(node);
        }
        else if (child != parent)
        {
            lowTime[node] = min(lowTime[node], discoveryTime[child]);
        }
    }

    if (parent == 0 && childCount > 1)
        articulationPoints.insert(node);
}

vector<bool> destructiveBob(int n, vector<vector<int>> edges, vector<int> queries)
{
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        graph[e[1]].push_back(e[0]);
    }

    dfs(1, 0);

    vector<bool> result;
    for (auto q : queries)
    {
        auto it = articulationPoints.find(q);
        result.push_back(it != end(articulationPoints));
    }

    return result;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++)
    {
		int x, y;
		cin >> x >> y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	}

	dfs(1, 0);

	for (auto x : articulationPoints)
        cout << x << '\n';

	return 0;
}
