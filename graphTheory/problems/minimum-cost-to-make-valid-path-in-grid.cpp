#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;

int minCost(vector<vector<int>> grid)
{
    int m = grid.size();
    int n = grid[0].size();
    int dr[4] = {0,0,1,-1};
    int dc[4] = {1,-1,0,0};

    map<pair<int,int>, vector<vector<int>>> graph;
    for (int r = 0; r < m; r++)
    {
        for (int c = 0; c < n; c++)
        {
            for (int i = 0; i < 4; i++)
            {
                int rr = r + dr[i];
                int cc = c + dc[i];

                if (rr >= 0 && rr < m && cc >= 0 && cc < n)
                {
                    int path = grid[r][c] - 1;
                    graph[{r,c}].push_back({rr,cc,(path == i ? 0 : 1)});
                }
            }
        }
    }

    deque<pair<int, int>> Q;
    Q.push_back({0,0});

    set<pair<int, int>> visited;
    map<pair<int, int>, int> dist;
    dist[{0,0}] = 0;


    while(!Q.empty())
    {
        auto node = Q.front();
        Q.pop_front();
        visited.insert(node);

        for (const auto& child : graph[node])
        {
            pair<int, int> childNode(child[0], child[1]);
            int weight = child[2];

            // if we have already visited this node, skip it
            auto it = visited.find(childNode);
            if (it != end(visited))
                continue;

            int currentDist = dist.find(childNode) == end(dist) ? INT_MAX : dist[childNode];

            dist[childNode] = min(currentDist, dist[node] + weight);
            if (weight == 0)
                Q.push_front(childNode);
            else
                Q.push_back(childNode);
        }
    }

    return dist[{m-1,n-1}];
}

int main()
{
    int res = minCost({{1,1,3},
                       {3,2,2},
                       {1,1,4}});
}
