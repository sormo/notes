#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

struct Node
{
    Node(char v) : value(v) {}

    char value = '\0';
    unordered_map<char, Node*> nodes;
    string word;
};

Node* createTrie(const vector<string>& words)
{
    Node* parent = new Node('\0');
    for (const auto& w : words)
    {
        Node* node = parent;
        for (int i = 0; i < w.size(); i++)
        {
            if (node->nodes.contains(w[i]))
            {
                node = node->nodes[w[i]];
            }
            else
            {
                auto newNode = new Node(w[i]);
                node->nodes[w[i]] = newNode;
                node = newNode;
            }
        }
        node->word = w;
    }
    return parent;
}

void dfs(int row, int col, const vector<vector<char>>& matrix, vector<vector<bool>>& visited, Node* trie, unordered_set<string>& result)
{
    if (!trie->word.empty())
    {
        result.insert(trie->word);
    }

    static const int dx[] = {0,  0, 1, -1,  1, -1, 1, -1};
    static const int dy[] = {1, -1, 0,  0, -1,  1, 1, -1};

    for (int i = 0; i < 8; i++)
    {
        int childRow = row + dx[i];
        int childCol = col + dy[i];
        if (childRow < 0 || childRow >= matrix.size() || childCol < 0 || childCol >= matrix[0].size())
            continue;

        if (visited[childRow][childCol])
            continue;

        // this can be done better
        if (!trie->nodes.contains(matrix[childRow][childCol]))
            continue;

        visited[childRow][childCol] = true;

        dfs(childRow, childCol, matrix, visited, trie->nodes[matrix[childRow][childCol]], result);

        visited[childRow][childCol] = false;
    }
}

vector<string> solve(const vector<vector<char>>& matrix, const vector<string>& words)
{
    auto trie = createTrie(words);

    unordered_set<string> result;
    vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].size(), false));
    for (int r = 0; r < matrix.size(); r++)
    {
        for (int c = 0; c < matrix[r].size(); c++)
        {
            if (trie->nodes.contains(matrix[r][c]))
                dfs(r, c, matrix, visited, trie->nodes[matrix[r][c]], result);
        }
    }

    vector<string> vectorResult;
    for (auto& w : result)
        vectorResult.push_back(w);

    return vectorResult;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int row, col;
    cin >> row >> col;

    vector<vector<char>> matrix(row, vector<char>(col, ' '));

    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            char v;
            cin >> v;
            matrix[r][c] = v;
        }
    }

    int wordsNum;
    cin >> wordsNum;

    vector<string> words(wordsNum);
    for (int i = 0; i < wordsNum; i++)
        cin >> words[i];

    auto result = solve(matrix, words);

    for (const auto& w : result)
        cout << w << "\n";
}