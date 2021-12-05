#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

std::vector<std::vector<int>> grid;
int graphSize;

std::set<std::pair<int32_t, int32_t>> visited;
std::map<std::pair<int32_t, int32_t>, int> discovery;
std::map<std::pair<int32_t, int32_t>, int> low;
std::set<std::pair<int32_t, int32_t>> articulationPoints;
int32_t index = 1;

void dfs(std::pair<int, int> node, std::pair<int, int> parent)
{
    static const int32_t dr[] = { 0,0,1,-1 };
    static const int32_t dc[] = { 1,-1,0,0 };

    visited.insert(node);
    discovery[node] = low[node] = index++;

    int childCount = 0;
    for (int32_t i = 0; i < 4; i++)
    {
        int32_t rr = node.first + dr[i];
        int32_t cc = node.second + dc[i];

        if (rr < 0 || rr >= graphSize || cc < 0 || cc >= graphSize)
            continue;

        // walls are not part of graph
        if (grid[rr][cc])
            continue;

        std::pair<int32_t, int32_t> child(rr, cc);

        if (!visited.contains(child))
        {
            dfs(child, node);
            low[node] = std::min(low[node], low[child]);
            childCount++;

            // if current node is not root and all backedges in subtree of child points at most to current node
            // then current node is articulation point
            if (parent != std::pair<int, int>(-1, -1) && low[child] >= discovery[node])
                articulationPoints.insert(node);
        }
        else if (child != parent)
        {
            low[node] = std::min(low[node], discovery[child]);
        }
    }

    // if current node is parrent it is articulation point if it contains more then one child
    if (parent == std::pair<int, int>(-1, -1) && childCount > 1)
        articulationPoints.insert(node);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin >> graphSize;
    grid = std::vector<std::vector<int>>(graphSize, std::vector<int>(graphSize, false));

    for (int r = 0; r < graphSize; r++)
    {
        for (int c = 0; c < graphSize; c++)
        {
            bool isWall;
            cin >> isWall;
            grid[r][c] = isWall;
        }
    }

    for (int r = 0; r < graphSize; r++)
    {
        for (int c = 0; c < graphSize; c++)
        {
            if (grid[r][c])
                continue;
            dfs({r, c}, {-1, -1});
            break;
        }
    }

	for (auto x : articulationPoints)
        cout << x.first << " " << x.second << '\n';

	return 0;
}
