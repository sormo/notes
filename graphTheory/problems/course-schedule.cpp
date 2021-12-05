#include<bits/stdc++.h>
using namespace std;

vector<int> findOrder(int numCourses, vector<vector<int>> prerequisites)
{
    vector<vector<int>> graph(numCourses, vector<int>());
    for (const auto& prerequisit : prerequisites)
        graph[prerequisit[1]].push_back(prerequisit[0]);
        
    vector<int> indegree(numCourses, 0);
    for (int i = 0; i < numCourses; i++)
    {
        for (int child : graph[i])
            indegree[child]++;
    }

    vector<int> result;
    set<int> candidates;

    // pick all candidates with no prerequisities
    for (int i = 0; i < numCourses; i++)
    {
        if (indegree[i] == 0)
            candidates.insert(i);
    }

    while(!candidates.empty())
    {
        // pick smallest candidate (set is sorted)
        int candidate = *candidates.begin();
        candidates.erase(candidates.begin());

        // push it to result (result will have to be reversed at the end)
        result.push_back(candidate);
        
        // decreese indegree for all childs of candidate
        for (int child : graph[candidate])
        {
            indegree[child]--;
            // if no prerequisities left add it as candidate
            if (indegree[child] == 0)
                candidates.insert(child);
        }
    }

    return result;
}
