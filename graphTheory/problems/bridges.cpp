#include <vector>
#include <set>
#include <iostream>
using namespace std;

const int N = 1e5;

vector<int> graph[N];

bool visited[N];

int discoveryTime[N];
int lowTime[N];
int index = 1;

vector<pair<int, int>> bridges;
set<int> articulationPoints;

void dfs(int node, int parent)
{
	visited[node] = true;
	discoveryTime[node] = lowTime[node] = index++;

	int childCount = 0;
	for (auto child : graph[node])
    {
		if (!visited[child])
        {
			dfs(child, node);
			childCount++;
			// we know low and disc of x
			lowTime[node] = min(lowTime[node], lowTime[child]);

			// bridges
            // lowTime[child] - discovery time to which we can get by
            // following single backedge in subtree of child
            // 
            // this means that all backedges within subtree of child points
            // somewhere below node (into the subtree of child)
			if (lowTime[child] > discoveryTime[node])
				bridges.push_back({node, child});

			// articulation points
			if (parent != 0 && lowTime[child] >= discoveryTime[node])
				articulationPoints.insert(node);
		}
		else if (child != parent)
        {
			// backedge
			lowTime[node] = min(lowTime[node], discoveryTime[child]);
		}
	}

	// root is an articulation point if it has more then one child
	if (parent == 0 && childCount > 1)
		articulationPoints.insert(node);
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

	for (auto x : bridges)
		cout << x.first << " " << x.second << '\n';

	return 0;
}