#include<bits/stdc++.h>
using namespace std;

int getNumOfDiffs(const string& w1, const string& w2)
{
    int result = 0;
    for (size_t i = 0; i < w1.size(); i++)
        result += w1[i] == w2[i] ? 0 : 1;
    return result;
}

int ladderLength(string beginWord, string endWord, vector<string> wordList)
{
    map<string, vector<string>> graph;
    
    if (find(begin(wordList), end(wordList), beginWord) == end(wordList))
        wordList.push_back(beginWord);
    
    for (const string& word : wordList)
    {
        vector<string> childs;
        for (const string& otherWord : wordList)
        {
            if (getNumOfDiffs(word, otherWord) == 1)
                childs.push_back(otherWord);
        }
        graph[word] = childs;
    }
    
    // bfs
    map<string, int> dists;
    set<string> visited;
    queue<string> bfs;
    
    bfs.push(beginWord);
    dists[beginWord] = 1;
    visited.insert(beginWord);
    
    while(!bfs.empty())
    {
        string current = bfs.front();
        bfs.pop();
        
        for (const string& child : graph[current])
        {
            if (visited.find(child) != end(visited))
                continue;
            
            dists[child] = dists[current] + 1;
            visited.insert(child);
            bfs.push(child);
        }
    }
    
    return dists.find(endWord) == end(dists) ? 0 : dists[endWord];
}
