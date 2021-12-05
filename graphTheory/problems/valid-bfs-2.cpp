#include <vector>
#include <string>
#include <queue>
#include <map>
#include <iostream>
using namespace std;

bool validBfs(int n, vector<int> sequence , vector<vector<int>> edges)
{
    vector<vector<int>> graph(n + 1, vector<int>());
    for (const auto& e : edges)
    {
        graph[e[0]].push_back(e[1]);
        //graph[e[1]].push_back(e[0]);
    }
    
    map<int, int> sequenceMap;
    for (int i = 0; i < sequence.size(); i++)
        sequenceMap[sequence[i]] = i;

    for (auto& childs : graph)
    {
        sort(begin(childs), end(childs), [&sequenceMap](int a, int b)
        {
            return sequenceMap[a] < sequenceMap[b];
        });
    }

    vector<int> testSequence;
    vector<bool> visited(n + 1, false);
    queue<int> bfs;
    
    bfs.push(sequence[0]);
    visited[sequence[0]] = true;

    while(!bfs.empty())
    {
        int n = bfs.front();
        bfs.pop();

        testSequence.push_back(n);

        for (int c : graph[n])
        {
            if (visited[c])
                continue;
                
            visited[c] = true;
            bfs.push(c);
        }
    }

    for (int i = 0; i < sequence.size(); i++)
    {
        if (sequence[i] != testSequence[i])
            return false;
    }

    return true;
}

int main()
{
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n;
    cin >> n;

    vector<vector<int>> edges(n - 1, vector<int>());
    for (int i = 0; i < n - 1; i++)
    {
        int e1, e2;
        cin >> e1 >> e2;

        edges[i] = { e1, e2 };
    }

    vector<int> sequence;
    for (int i = 0; i < n; i++)
    {
        int j;
        cin >> j;
        sequence.push_back(j);
    }

    cout << (validBfs(n, sequence, edges) ? "Yes" : "No");

    return 0;
}
