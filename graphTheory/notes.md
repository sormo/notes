# Graph Types

* directed graph
* undirected graph

* weighted graph
* unweighted graph

# Representations

* adjacency list
** each node has list of neighbors
* adjacency matrix
** matrix of v x v (v is number of nodes -> very big)
* edge list
** list of edges (tuples from, to or triples from, to, weight)
* implicit graph
** we know or we can compute neighbors on the fly

## Adjacency List vs Adjacency Matrix

In adjacency list it is easier to iterate over all neighbors of node
In adjacency matrix it is easier to check whether node is neighbor of some other node (but takes a lot of space)

# BFS - Breadth First Search

```c++
    queue<int> Q;
    vector<bool> visited(n + 1, false);
    vector<int> distance(n + 1, -1);
    
    Q.push(1);
    visited[1] = true;
    distance[1] = 0;
    
    while(!Q.empty())
    {
        int n = Q.front();
        Q.pop();
        
        for (const auto e : graph[n])
        {
            if (visited[e])
                continue;
            distance[e] = distance[n] + 1;
            visited[e] = true;
            Q.push(e);
        }
    }
```
Example: [Word Ladder](https://leetcode.com/problems/word-ladder) Create adjacency list from words and then traverse graph using BFS.

# DFS - Depth First Search

```c++
    void dfs(int node, vector<int>& visited, vector<vector<int>>& graph)
    {
        visited[node] = true;
        for (int child : graph[node])
        {
            if (visited[child])
                continue;
            dfs(child, visited, graph);
        }
    }
```
Example: [Max Area of Island](https://leetcode.com/problems/max-area-of-island) Simply do DFS from each 1 with fresh visited array
```c++
void dfs(int r, int c, vector<vector<int>>& visited, const vector<vector<int>>& grid)
{
    static const int dr[] = {1,-1,0,0};
    static const int dc[] = {0,0,1,-1};

    visited[r][c] = true;
    
    for (int i = 0; i < 4; i++)
    {
        int rr = r + dr[i];
        int cc = c + dc[i];
        
        if (rr >= 0 && rr < n && cc >= 0 && cc < n && grid[rr][cc] == 1 && !visited[rr][cc])
            visit(rr, cc, visited, grid);
    }
}
```

# Cycle Detection

## Undirected Graph

```c++
bool dfs(int node, int parent, vector<bool>& visited, const vector<vector<int>>& graph)
{
    visited[node] = true;
    
    for (int child : graph[node])
    {
        if (child == parent)
            continue;
        
        if (visited[child])
            return true;
        
        if (dfs(child, parent, visited, graph))
            return true;
    }
    
    return false;
}
```

## Directed Graph

```c++
bool dfs(int node, vector<int>& visited, vector<int>& currentBranch, const vector<vector<int>>& graph)
{
    visited[node] = true;
    currentBranch[node] = true;
    
    for (int child : graph[node])
    {
        if (visited[child])
        {
            if (currentBranch[child])
                return true;
            continue;
        }
        
        if (dfs(child, visited, currentBranch, graph))
            return true;
    }
    
    currentBranch[node] = false;
    
    return false;
}
```

# Bipartite Graph

Bipartite graph is graph that does not contain odd length cycle. Also nodes of bipartite graph can be divided into two groups
such that all edges goes from first group to second (no edge is contained within a group).

To determine whether graph is bipartite we can use colors. If we start coloring nodes from root `red` and `black` no two nodes can have same color and be connected with edge. If this will happen, graph is not bipartite.

# Directed Acyclic Graph - DAG

DAG is directed graph that does not contain cycle.

# Topological Ordering

is a linear ordering of vertices such that for every edge u->v, vertex u comes before v in the ordering. Possible only for DAG.

## BFS algorithm - Kahn

* compute in-degree for each node
* nodes with in-degree 0 push to queue
* while queue is not empty
* pop node, print it and decrement in-degree for it's child
* if any child has in-degree zero, push it to queue

Example: *course-schedule* when set is used instead of queue, lexicographically smallest ordering is found. 

## DFS algorithm

When leaving a node such that all childs of node has been visited, push node to front of list.

```c++
void dfs(int node, vector<int>& visited, const vector<vector<int>>& graph, vector<int>& result)
{
    visited[node] = true;

    for (auto child : graph[node])
    {
        if (visited[child])
            continue;
        dfs(child, visited, graph, result);
    }

    result.push_back(node);
    // !!! at the end result must be reversed
}
```

# Disjoint Set Union - DSU

Data structure with two operations:
* union
* find

```c++
int Find(int n, const vector<int>& parent)
{
    if (parent[n] == -1)
        return n;
    return Find(parent[n], parent);
}

void Union(int n1, int n2, vector<int>& parent)
{
    int p1 = Find(n1, parent);
    int p2 = Find(n2, parent);
    
    if (p1 != p2)
        parent[p2] = p1;
}
```

Example: *forest-detection* given edges, verify they form a forest. If any edge connects two nodes in same bucket, it's no tree. Each bucket of n nodes should have n-1 edges. 

Example: *communication-towers* towers are on grid and can communicate if are on same row/column. If a can communicate with b and with c then a can communicate with c. Find groups of towers that can communicate.

Example: *make-network-connected* move cables such that all computers are connected.

Example: *remove-edges* add edges to DSU while not creating cycle. If there is n-1 edges we have a tree and graph is connected.

## DSU Optimizations

### Union by Rank

```c++
void Union(int n1, int n2, vector<int>& parent, vector<int>& rank)
{
    int p1 = Find(n1, parent);
    int p2 = Find(n2, parent);
    
    if (p1 != p2)
    {
        if (rank[p1] < rank[p2])
        {
            parent[p1] = p2;
            rank[p2] += rank[p1]
        }
        else
        {
            parent[p2] = p1;
            rank[p1] += rank[p2]
        }
    }
}
```

### Path Compression

```c++
int Find(int n, const vector<int>& parent)
{
    if (parent[n] == -1)
        return n;
    parent[n] = Find(parent[n], parent);
    return parent[n];
}
```
# Minimum Spanning Tree - MST

MST of graph is tree that connects all nodes (tree with n-1 edges) and has minimum total cost.

## Prim's

Greedy algorithm. Pick best edge out of the subset of edges.

* Insert initial node with zero weight to min-heap (key is weight)
* While heap is not empty
* Pick edge at the top of heap (minimum weight)
* Include it in MST
* Add childs of node to min-heap (key is weight of edge to child, and value is child)

```c++
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
    vector<bool> visited(n + 1, false);
    
    Q.push({0, 1});
    
    int result = 0;
    while(!Q.empty())
    {
        auto weight = Q.top().first;
        auto node = Q.top().second;
        Q.pop();
        
        if (visited[node])
            continue;
        visited[node] = true;
        
        result += weight;
        
        for (const auto& child : graph[node])
            queue.push({child.second, child.first});
    }
```

## Kruskal

* Sort edges according to weight
* Pick edge if it doesn't form a cycle (using DSU)

```c++
    vector<vector<int>> edges; // each edge is vector: {weight, u, v}
    ...
    sort(begin(edges), end(edges)); // sort according to weight

    for (const auto& edge : edges)
    {
        int w = edge[0], u = edge[1], v = edge[v];
        if (find(u, parents) != find(v, parents))
        {
            union(u, v, parents);
            result += w; // pick edge
        }
    }

```

# Shortest Paths

## Dijkstra

Usable for graphs with non-negative weights. Greedy algorithm, pick node with smallest distance found so far.
* Maintain a min-heap or set that will contain distance to root node as a key
* Pick first node from the set and include it in path
* Iterate over childs and add/update it's distance in set

```c++
    // distance, node
    set<pair<int, int>> currentNodes;
    currentNodes.insert({0, 1});
    
    while(!currentNodes.empty())
    {
        int node = currentNodes.begin()->second;
        int nodeDistance = currentNodes.begin()->first;
        currentNodes.erase(currentNodes.begin());

        for (const auto& child : graph[node])
        {
            int childNode = child.first;
            int edgeWeight = child.second;
            
            if (nodeDistance + edgeWeight < distances[childNode])
            {
                // here we need to also update existing distance to child (it may already exist in set)
                auto it = currentNodes.find({distances[childNode], childNode});
                if (it != currentNodes.end())
                    currentNodes.erase(it);

                currentNodes.insert({nodeDistance + edgeWeight, childNode});
                distances[childNode] = nodeDistance + edgeWeight;
                parents[childNode] = node;
            }
        }
    }
```

## Bellman-Ford

Usable for graph with negative edges. Shortest path does not exist if graph contains negative weight cycle.

For graph where V is number of nodes and E is number of edges
* repeat V - 1 times
* for each edge `u`->`v` check whether path to `v` isn't shorter using this edge through `u`

```c++
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 0; i <= V - 1; i++)
    {
        for (const auto& edge : edges)
        {
            int u = edge[0], v = edge[1], w = edge[2];
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // one last iteration over edges, if anything changes, graph contains negative weight cycle
    for (const auto& edge : edges)
    {
        int u = edge[0], v = edge[1], w = edge[2];
        if (dist[u] != INT_MAX && dist[u] + w < dist[v])
            printf("Graph contains negative weight cycle");
    }
```

Example: `cheapest-flight-within-k-stops` to update distances in layers like BFS (first iteration get distances one stop away and so on), use temporary array where distances are updated during iteration over edges.

## Floyd-Warshall

All pair shortest path in O(n^3)

```c++
    for (int i = 0; i <= n; i++)
        distances[i][i] = 0;
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                if (distances[i][j] > distances[i][k] + distances[k][j])
                    distances[i][j] = distances[i][k] + distances[k][j];
            }
        }
    }
```

Example: see `travel-by-car` for path reconstruction

# Traveling Salesman Problem - TSP

Brute force:
```c++
int tsp(vector<vector<int>>& distances, int visitedCities, int currentCity, int n)
{
    if (visitedCities == (1 << n) - 1)
        return distances[currentCity][0];

    int result = INT_MAX;
    for (int city = 0; city < n; city++)
    {
        if (visitedCities & (1 << city) != 0)
            continue;
        int tmp = dist[currentCity][city] + tsp(distances, visitedCities | (1 << city), city, n);
        result = min(tmp, result);
    }

    return result;
}
```

In DP solution store `dp[visitedCities][currentCity]` as a memoization.

# Flood Fill

Using DFS in grid

Counting number of islands:
```c++
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

void floodFill(int x, int y)
{
    visited[x][y] = true;
    for (int i = 0; i < 4; i++)
    {
        int xx = x + dx[i], yy = y + dy[i];
        if (xx >= 0 && xx < n && yy >= 0 && yy < m && !visited[xx][yy])
        {
            floodFill(xx, yy);
        }
    }
}

//...
    int totalCount = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i][j] == 1)
            {
                totalCount++;
                floodFill(i, j);
            }
        }
    }
```
Count index can be used to color different islands. Size of island can be found by counting cells with same color. 

# Multi-Source BFS

Example: `rotten-oranges` every minute a rotten orange will make adjacent oranges also rotten.

Example: `shortest-bridge` return smallest number of water cells that must be changed to connect two islands. Push all nodes of single island to BFS queue and find shortest path to any island cell of other island.

Example: `highest-peak` get highest peak of island such that height of water is 0 and height can increase only by one. Push all the water cells to BFS queue, setting its distance to 0. Then do BFS increasing height for non-water cell (taking minimum).
```c++
    while(!Q.empty())
    {
        int r = Q.front().first;
        int c = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++)
        {
            int rr = r + dr[i];
            int cc = c + dc[i];

            if (rr >= 0 && rr < m && cc >= 0 && cc < n && distances[rr][cc] == INT_MAX)
            {
                distances[rr][cc] = min(distances[rr][cc], distances[r][c] + 1);
                Q.push({rr, cc});
            }
        }
    }
```

# DFS-Tree and Backedges

Edges traversed during DFS forms a tree (n-1 edges). Other edges which are not traversed (because destination node is already visited) are backedges and forms a cycle in graph.

## Detect Backedge in Undirected Graph

In undirected graph any edge that connects node to already visited node (during DFS) is backedge.

## Detect Backedge in Directed Graph

In directed graph node must be in `call stack`. That is stack of nodes of current path. Such nodes can be simply marked in DSF when entering and un-marked when leaving:
```c++
void dfs(int node, int parent)
{
    // node in call stack
    visited[node] = true;
    for (auto child : graph[node])
    {
        if (!visited[child])
        {
            dfs(child, node);
        }
        else if (child != parent && visited[child])
        {
            // backedge
            cycle = true;
        }
    }
    // node not in call stack
    visited[node] = false;
    return;
}
```

## Printing Cycle

To print all cycles, print cycle when backedge found by iterating parents array:
```c++
void dfs(int node, int parent)
{
    // visited and in call stack
    visited[node] = 1;
    parents[node] = parent;
    for (auto child : graph[node])
    {
        if (visited[child] == 0)
        {
            dfs(child, node);
        }
        else if (child != parent && visited[child] == 1)
        {
            // backedge
            int u = node, v = child;
            while (u != v)
            {
                cout << u << " ";
                u = parents[u];
            }
            cout << u << "\n";
        }
    }
    // visited and not in call stack
    visited[node] = 2;
}
```

# Articulation Points - Cut Vertices

`Articulation point` or `cut vertex` is a vertex whose removal will increase the number of connected components.

Articulation points can be identified in single DFS. Following information is maintained during DFS:
1. depth of vertex
2. lowest depth reachable using backedge from subtree of vertex - `lowpoint`

Non-root vertex `v` is articulation point if it has some child `y` where `lowpoint(y) >= depth(v)` (in other words if following some backedge in subtree of `y` we can reach at most `v`)
Root vertex is articulation point if it has more than one child (excluding backedges).

```c++
void dfs(int node, int parent = 0)
{
    visited[node] = true;
    depth[node] = lowpoint[node] = time++;

    int childCount = 0;
    for (auto child : graph[node])
    {
        if (!visited[child])
        {
            childCount++;

            dfs(child, node);

            lowpoint[node] = min(lowpoint[node], lowpoint[child]);

            // articulation points
            if (parent != 0 && lowpoint[child] >= depth[node])
                articulationPoints.insert(node);
        }
        else if (x != par)
        {
            // backedge
            lowpoint[node] = min(lowpoint[node], depth[child]);
        }
    }

    // root is an arti or not
    if (parent == 0 && childCount > 1)
        articulationPoints.insert(node);
}
```
Note: regarding `lowpoint`, initially it's set to depth. So initially each child has higher `lowpoint` then it's parent. It can be set to some lower value through backedge. This lower `lowpoint` value is propagated to parents until parent with same `lowpoint` value is found.

# Bridges

Bridge is an edge of graph whose deletion will increase number of connected components. Similar algorithm is used as for articulation points. Edge between parent `v` and child `y` is bridge if `lowpoint(y) > depth(v)`. In other words if all backedges of subtree of `y` is contained within that subtree.

```c++
void dfs(int node, int parent)
{
    visited[node] = true;
    depth[node] = lowpoint[node] = time++;

    for (auto child : graph[node])
    {
        if (!visited[child])
        {
            dfs(child, node);

            lowpoint[node] = min(lowpoint[node], lowpoint[child]);

            // bridge
            if (lowpoint[child] >= depth[node])
                bridges.push_back({node, child});
        }
        else if (x != par)
        {
            // backedge
            lowpoint[node] = min(lowpoint[node], depth[child]);
        }
    }
}
```

# Strongly Connected Components - SCC

A directed graph is called strongly connected if there is a path between every pair of vertices (in each direction).

Kosaraju algorithm:
* find topological ordering
* visit nodes using dfs in reversed topological order

```c++
// topological ordering of directed graph
void dfs1(int node)
{
    visited1[node] = true;
    for (auto child : graph[node])
    {
        if (!visited1[child])
            dfs1(child);
    }
    topologicalOrder.push_back(node);
}

// simple DFS
void dfs2(int node, int componentIndex)
{
    visited2[node] = true;
    components[node] = componentIndex;
    for (auto child : graph[node])
    {
        if (!visited[child])
            dfs2(child, componentIndex);
    }
}

void main()
{
    // first dfs is to find topological ordering
    for (int i = 1; i <= n; i++)
    {
        if (!visited1[i])
            dfs1(i);
    }

    reverse(topologicalOrder.begin(), topologicalOrder.end());

    // second dfs is to identify SCCs
    int componentIndex = 1;
    for (auto node : topologicalOrder)
    {
        if (!visited2[node])
            dfs2(node, componentIndex++);
    }
}
```

# Trees

* is a subset of graph
* does not contain cycle
* there is single path between each pair of nodes
* is connected graph
* for `n` nodes graph there is `n - 1` edges
* adding new edge to tree will create cycle
* every node has one parent (except root node)

Tree can be rooted on arbitrary `root` node. When tree is rooted, we can talk about `child`, `parent`, `ancestor`, `sibling`, `leaf`, `subtree`.

When performing DFS on tree it is enough to check for parent instead of visited array:
```c++
void dfs(int node, int parent)
{
    for (int child : graph[node])
    {
        if (child != parent)
            dfs(child, node);
    }
}
```

Printing all ancestors of node `x`
```c++
void dfs(int node, int parent)
{
    parents[node] = parent;
    for (auto child : graph[node])
    {
        if (child != parent)
        {
            dfs(child, node);
        }
    }
}

    // parent of root is zero
    while (x != 0)
    {
        cout << x << '\n';
        x = parents[x];
    }
```

To find `tree diameter` which is longest path in the tree:
* find farthest node `u` from arbitrary root node
* find farthest node `v` from `u` node

# Euler Tour

`Walk` of graph is sequence of edges that joins vertices in some order.
`Trail` of graph is a walk without repeated edges.
`Euler path` is a trail of graph that visits every edge exactly once (allow revisiting vertices).
`Euler tour` (or circuit) is euler path that starts and end at the same vertex.

Tree can be represented using Euler tour known as `Euler tour representation`.

```c++
void dfs(int node, int parent)
{
    timeIn[node] = time++;
    for (auto child : graph[node])
    {
        if (child == parent)
            continue;
        dfs(child, node);
    }
    timeOut[node] = time;
}
```
```
   1
 2   3
   4   5

         1 2 3 4 5
timeIn : 1 2 3 4 5
timeOut: 5 2 5 4 5
```

To verify whether node `u` is in the subtree of `v`:
```c++
    if (timeIn[u] >= timeIn[v] && timeOut[u] <= timeOut[v])
        // u is in subtree of v
```

To verify whether `u` is ancestor of `v`:
```c++
    if (timeIn[u] <= timeIn[v] && timeOut[u] >= timeOut[v])
        // u is ancestor of v
```

To flatten the `timeIn` and `timeOut`:
```c++
    for (int i = 1; i <= n; i++)
        flattened[timeIn[i]] = i;
```

# Lowest Common Ancestor - LCA

LCA is vertex that lies on path from root to `v1` and also on path from root to `v2` and this vertex is lowest.
LCA also lies on shortest path from `v1` to `v2`.

For LCA we need to find `depths` which is distance from root and parents:
```c++
void dfs(int node, int parent)
{
	parents[node] = parent;
	depths[node] = depths[parent] + 1;
	for (auto child : graph[node])
    {
		if (child != parent)
			dfs(child, node);
	}
}
```

Brute force algorithm
```c++
int LCA(int u, int v)
{
	if (u == v)
        return u;

	if (depths[u] < depths[v])
        swap(u, v);
	// make depth of u more than depth of v

	int diff = depths[u] - depths[v];

	// depth of both nodes same
	while (diff--)
		u = parents[u];

	// until they are equal nodes keep climbing
	while (u != v)
    {
		u = parents[u];
		v = parents[v];
	}

	return u;
}
```

## Binary Lifting Optimization

During preprocessing fill in array `parents` where `parents[i][j]` means:
__for i-th node 2^j-th ancestor__

That means `parents[2][0]` is first ancestor of node 2. `parents[2][2]` is 4-th ancestor of node 2.

```c++
void dfs(int node, int parent)
{
    timeIn[node] = ++time;

    parents[node][0] = parent;
    for (int i = 1; i <= limit; ++i)
        parents[node][i] = parents[parents[node][i-1]][i-1];

    for (int child : graph[node])
    {
        if (child != parent)
            dfs(child, node);
    }

    timeOut[node] = time;
}
```
`limit` is set to `ceil(log2(n))` which is second log of number of vertices rounded up.
Magic happening here:
```c++
    parents[node][i] = parents[parents[node][i-1]][i-1];
```
for example 4th ancestor of node 2 is 2nd ancestor of 2nd ancestor
```
    secondAncestor = parents[2][1];
    parents[2][2] = parents[secondAncestor][1].
```

```c++
    int lca(int u, int v)
    {
        if (isAncestor(u, v))
            return u;
        if (isAncestor(v, u))
            return v;
        for (int i = limit; i >= 0; --i)
        {
            if (!isAncestor(parents[u][i], v))
                u = parents[u][i];
        }
        return parents[u][0];
    }
```

```c++
    int lca(int u, int v) {
        if (u == v)
            return u;
        if (depths[u] < depths[v])
            swap(u, v);
        int diff = depths[u] - depths[v];
        for (int j = limit - 1; j >= 0; j--)
        {
            if ((diff >> j) & 1)
            {
                // jth bit of diff is set
                u = parents[u][j];
            }
        }
        // u and v are on the same level
        for (int j = M - 1; j >= 0; j--)
        {
            if (parents[u][j] != parents[v][j])
            {
                u = parents[u][j];
                v = parents[v][j];
            }
        }

        // parents[v][0]
        return parents[u][0];
    }
```

# Re-rooting of Trees

Example: when tree is rooted on some node, compute sum of all the subtree sizes:
```
     1
    2 3
   4 5
1 -> for node 1 subtree size is 5
2 -> 3
4 -> 1
5 -> 1
3 -> 1
```
When the tree is rooted on 1, sum of subtree sizes is 11. When the same tree is rooted on 4:
```
     4
     2
    5 1
      3
```
sum of subtree sizes is 5 + 4 + 1 + 2 + 1 = 13
Find the maximum sum of subtree sizes.

DFS to find sum of subtree sizes:
```c++
int dfs(int node, int parent)
{
    subtreeSize[node] = 1;

    int sum = 0;
    for (auto child : graph[node])
    {
        if (child == parent)
            continue;
        sum += dfs(child, node);
        subtreeSize[node] += sub[child];
    }
    sum += subtreeSize[node];

    return sum;
}
```
Brute-force solution will iterate over all vertices calling DFS above for each making it root. This take O(n^2).

Re-rooting solution will take O(n) time. In DFS we will compute the subtree sizes but we won't compute whole sum of subtree sizes but create `dp` in which `dp[i]` is sum of subtree sizes up to node `i`

```c++
void dfs(int node, int parent)
{
    subtreeSize[node] = 1;
    dp[node] = 0;

    for (auto child : graph[node])
    {
        if (child == parent)
            continue;
        dp[node] += dp[child];
        subtreeSize[node] += sub[child];
    }
    dp[node] += dp[node];
}
```

The program will initialize `dp` and `subtreeSize` arrays in a way such that vertex 1 is the node. Then `dfsReroot`:
```c++
    dfs(1, 0);
    dfsReroot(1, 0);
```
`dfsReroot` expects that `dp` and `subtreeSize` arrays are correctly set according to `root`. It will update the answer and then re-root to all childs calling self recursively.
```c++
void dfsReroot(int root, int parent)
{
    answer = max(answer, dp[root]);

    for (auto child : graph[root])
    {
        if (child == parent)
            continue;
    
        // remove child from subtree of root
        dp[root] -= dp[child];
        dp[root] -= sub[child];
        sub[root] -= sub[child];
        // now add root as the subtree of child
        sub[child] += sub[root];
        dp[child] += dp[root];
        dp[child] += sub[root];

        dfsReroot(child, root);

        // come back from child
        // rollback the changes as original tree
        dp[child] -= sub[root];
        dp[child] -= dp[root];
        sub[child] -= sub[root];
        sub[root] += sub[child];
        dp[root] += sub[child];
        dp[root] += dp[child];
    }
}
```
Example: `distance-sum` distance sum is defined as the sum of the distances from the node to all other nodes. Return an array containing distance sum for all nodes.

Example: `maximum-white-subtree` tree contains black and white vertices. Find subtree of tree which will have maximum difference `count of white vertices - count of black vertices`.

Example: `capital-of-treeland` given a directed tree, choose root node such that minimum number of edges must be inverted. All nodes must be reachable from root node.

Example: `distance-in-tree` distance between two nodes in tree is defined as the number of edges that must be traversed from first node to second following the shortest path between them. Given positive number `k` find number of node pairs which has distance exactly `k`.

# Network Flow

Flow network is defined as directed graph involving `source(S)` and `sink(T)` and other nodes connected with edges. Each edge has assigned capacity, which is the maximum flow that edge can allow.

Total flow that is going out of S is total flow that is going to T. 

## Residual Graph

Residual graph has same vertices as original graph. For each edge there is:
* forward edge which represents `residual capacity` which is `capacity` of edge - `flow` currently flowing through edge
* backward edge which is equal to flow through this edge

For example we have edge which has capacity 10 and current flow through edge is 3. In residual network there will be froward edge with value 7 and backward edge with value 3.

## Augmenting Path

Any path from source to sink in residual graph.

## Ford-Fulkerson Algorithm

* construct residual graph and initialize `residual capacity` of each edge to it's capacity (forward edge) and `flow` to 0 (backward edge)
* while there is augmenting path between source and sink:
* * update residual network using this path

To find `augmenting path` in residual graph, run DFS from source and keep list of nodes of the path. If sink is reached, find `bottleneck` value of the path (smallest residual capacity).
To update residual graph with augmenting path, just increase flow and decrease residual capacity with bottleneck value for each edge of the path.

Note: if BFS is used instead of DFS algorithm is called Edmond-Karp.

Running time is O(maxFlow * E)

## Dinic's Algorithm

1. initialize residual graph
2. construct level graph
3. while sink is reachable from source
4.    while there is augmenting path from source to sink in residual graph
5.        update residual graph with augmenting path
6.    goto 2.

Level graph means assigning nodes with distances from source node (using BFS).
* do not consider edges with residual capacity equal to 0
* do not consider nodes which does not lead to sink

__Level in augmenting path can only increase.__

```c++
struct Dinic
{
    Dinic(int source, int sink, int nodeCount)
        : source(source), sink(sink)
    {
        graph.resize(nodeCount);
    }

    void AddEdge(int from, int to, long long flow)
    {
        // residual capacity
        edges.push_back({from, to, flow});
        graph[from].push_back(edges.size() - 1);
        // actual flow
        edges.push_back({to, from, 0});
        graph[to].push_back(edges.size() - 1);
    }

    long long MaximumFlow()
    {
        long long result = 0;
        while(CreateLevelGraph())
        {
            // augment using augmenting path while possible
            while(long long flow = Augment())
            {
                result += flow;
            }
        }
        return result;
    }

private:
    bool CreateLevelGraph()
    {
        levels.clear();
        levels.resize(graph.size(), -1);

        queue<int> Q;
        Q.push(source);
        levels[source] = 0;

        // perform BFS storing distance to source
        // (use levels also as visited array)
        // (do not use edge which has 0 flow)

        while(!Q.empty())
        {
            int node = Q.front();
            Q.pop();

            for (auto edgeIndex : graph[node])
            {
                int child = edges[edgeIndex].to;
                long long flow = edges[edgeIndex].flow;

                if (flow != 0 && levels[child] == -1)
                {
                    levels[child] = levels[node] + 1;
                    Q.push(child);
                }
            }
        }

        return levels[sink] != -1;
    }

    long long Augment()
    {
        vector<bool> visited(graph.size(), false);

        return AugmentDfs(source, 1e9 + 1, visited);
    }

    long long AugmentDfs(int node, long long flow, vector<bool>& visited)
    {
        if (node == sink)
            return flow;

        for (auto edgeIndex : graph[node])
        {
            int child = edges[edgeIndex].to;
            long long childFlow = edges[edgeIndex].flow;

            if (visited[child])
                continue;

            // important thing here is that we are allowed to move only up the level
            if (levels[node] + 1 != levels[child])
                continue;

            long long bottleneck = AugmentDfs(child, min(flow, childFlow), visited);
            if (bottleneck != 0)
            {
                // found augmenting path, augment the flows in edges
                edges[edgeIndex].flow -= bottleneck;
                edges[edgeIndex ^ 1].flow += bottleneck;
                // xor 1 above means -1 for even and +1 for odd values

                return bottleneck;
            }
        }

        return 0;
    }

    struct Edge
    {
        int from;
        int to;
        long long flow;
    };

    int source;
    int sink;
    vector<vector<int>> graph;
    vector<Edge> edges;
    vector<int> levels;
};
```

## Bipartite Matching

Matching between two sets (bipartite graph)
__Assignment Problem__ 
Problem has number of agents and tasks. Agents can be assigned to at most one task. Find agent-task assignments such that as most tasks are done.  

Create bipartite graph where agent is connected to task if he is able to perform the task. Connect Source node to each agent with edge with capacity 1 (each agent can perform one task) and each task to sink node (also edge with capacity one).

Similarly problem with assigning chocolate to student. From Source there is an edge to each student. Capacity of this edge represents number of chocolates particular student can get. Student is connected with chocolate if he likes (is able to get) particular chocolate. Each chocolate is connected to Sink node with edge (capacity of that edge represents number of chocolate available).

__Rook Attack__
Place maximum number of rooks on chessboard with some squares cut out.

Again create bipartite graph where one set is set of rows and other set is set of columns. Row x is connected with column y if cell x,y is not cut out. Edges from source and one set and from other set to sink has all capacities one.

__Parking__
Match cars with parking spot. Additionally the time it takes for all cars to find a parking spot must be minimized. (for example delivery riders)

Create bipartite graph where one set is cars and other set is parking slots. Capacity of the edge between those two is distance (between particular car and slot).

Construct bipartite graph including distances only up to X. If it is possible to park all cars, try smaller X. (use binary search to find optimal X).
