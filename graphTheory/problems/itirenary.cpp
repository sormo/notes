#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

void dfs(string n, map<string, vector<string>>& graph, vector<string>& result)
{
    result.push_back(n);
    
    if (graph[n].size() == 0)
        return;
        
    string next = graph[n][0];
    graph[n].erase(begin(graph[n]));
    
    dfs(next, graph, result);
}

vector<string> findItinerary(vector<vector<string>> tickets)
{
    map<string, vector<string>> graph;
    auto addToMap = [&graph](const string& e1, const string& e2)
    {
        auto it = graph.find(e1);
        if (it != end(graph))
            it->second.push_back(e2);
        else
            graph[e1] = { e2 };
    };
    
    for (const auto& e : tickets)
    {
        addToMap(e[0], e[1]);
    }
    
    for (auto it = begin(graph); it != end(graph); it++)
        sort(begin(it->second), end(it->second));
    
    vector<string> result;
    dfs("JFK", graph, result);
    
    return result;
}

int main()
{
    std::string t;

    std::cin >> t;

    std::cout << "Hello " << t << "\n";
    std::cout << "Hello seems like it's working" << "\n";

    return 0;
}
