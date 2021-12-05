#include <vector>
#include <map>

using namespace std;

vector<int> reconstructPath(int from, int to, const vector<vector<int>>& nextNode)
{
    if (nextNode[from][to] == -1)
        return {};

    vector<int> result;
    result.push_back(from);

    while(from != to)
    {
        from = nextNode[from][to];
        if (from == -1)
            return {};

        result.push_back(from);
    }

    return result;
}

vector<int> travelByCar(int n,int l, vector<vector<int>> edges, vector<vector<int>> queries)
{
    vector<vector<int>> distances(n+1, vector<int>(n+1, 1e8));
    vector<vector<int>> nextNode(n+1, vector<int>(n+1, -1));
    
    for (const auto& e : edges)
    {
        if (e[2] > l)
            continue;
        distances[e[0]][e[1]] = distances[e[1]][e[0]] = e[2];
        nextNode[e[0]][e[1]] = e[1];
        nextNode[e[1]][e[0]] = e[0];
    }
    
    for (int i = 0; i <= n; i++)
    {
        distances[i][i] = 0;
        nextNode[i][i] = i;
    }
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= n; k++)
            {
                if (distances[i][j] > distances[i][k] + distances[k][j])
                {
                    distances[i][j] = distances[i][k] + distances[k][j];
                    nextNode[i][j] = nextNode[i][k];
                }
            }
        }
    }
    
    vector<int> result;
    for (const auto& q : queries)
    {
        if (q[0] == q[1])
        {
            result.push_back(0);
            continue;
        }

        auto path = reconstructPath(q[0], q[1], nextNode);
        if (path.empty())
        {
            result.push_back(-1);
            continue;
        }

        int count = 0;
        int fuel = l;
        for (int i = 1; i < path.size(); i++)
        {
            int distance = distances[path[i-1]][path[i]];
            fuel -= distance;
            if (fuel < 0)
            {
                count++;
                fuel = l - distance;
            }
        }
        result.push_back(count);
    }

    return result;
}

int main()
{

}
