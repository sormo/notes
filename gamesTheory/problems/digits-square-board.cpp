#include <vector>
#include <iostream>
#include <set>
#include <array>
using namespace std;

//                   0     1      2     3     4      5     6      7     8      9
bool primes[10] = { true, false, true, true, false, true, false, true, false, false };

using Memo = vector<vector<vector<vector<int>>>>;

// r2, c2 is non-inclusive
struct Board
{
    int r1;
    int c1;
    int r2;
    int c2;

    bool operator==(const Board& o) { return r1 == o.r1 && r2 == o.r2 && c1 == o.c1 && c2 == o.c2; }
};

int mex(const set<int>& states)
{
    int result = 0;
    while(states.find(result) != states.end())
        result++;
    return result;
}

bool isCuttable(const Board& board, const vector<vector<int>>& grid)
{
    for (int r = board.r1; r < board.r2; r++)
    {
        for (int c = board.c1; c < board.c2; c++)
        {
            if (!primes[grid[r][c]])
                return true;
        }
    }
    return false;
}

pair<Board, Board> cutAtRow(const Board& board, int row)
{
    Board board1 = board;
    board1.r2 = row;

    Board board2 = board;
    board2.r1 = row;

    return { board1, board2 };
}

pair<Board, Board> cutAtCol(const Board& board, int col)
{
    Board board1 = board;
    board1.c2 = col;

    Board board2 = board;
    board2.c1 = col;

    return { board1, board2 };
}

int grundy(const Board& board, const vector<vector<int>>& grid, Memo& memo)
{
    if (memo[board.r1][board.c1][board.r2][board.c2] != -1)
        return memo[board.r1][board.c1][board.r2][board.c2];

    if (board.r1 == board.r2 && board.c1 == board.c2)
        return 0;

    if (!isCuttable(board, grid))
        return 0;

    set<int> states;
    for (int r = board.r1 + 1; r < board.r2; r++)
    {
        auto [board1, board2] = cutAtRow(board, r);
        states.insert(grundy(board1, grid, memo) ^ grundy(board2, grid, memo));
    }

    for (int c = board.c1 + 1; c < board.c2; c++)
    {
        auto [board1, board2] = cutAtCol(board, c);
        states.insert(grundy(board1, grid, memo) ^ grundy(board2, grid, memo));
    }

    return memo[board.r1][board.c1][board.r2][board.c2] = mex(states);
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int t;
    cin >> t;
    while(t--)
    {
        int n;
        cin >> n;

        vector<vector<int>> grid(n, vector<int>(n, 0));
        for (int r = 0; r < n; r++)
        {
            for (int c = 0; c < n; c++)
            {
                cin >> grid[r][c];
            }
        }

        Memo memo(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, -1))));
        cout << (grundy({0, 0, n, n}, grid, memo) == 0 ? "Second" : "First") << "\n";
    }
}
