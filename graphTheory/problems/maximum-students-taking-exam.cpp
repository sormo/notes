#include <vector>
#include <iostream>
using namespace std;

bool isBitSet(int state, int bitIndex)
{
    int bitmask = 1 << bitIndex;

    return (state & bitmask) != 0;
}

bool isValidState(int state, const vector<char>& row, int stateBitCount)
{
    // 1. Verify whether state contains two neighbouring bits, if so this state can't be used.
    // 2. Verify whether the bit set in the state match with '.' in the row.
    bool stateSet = false;
    for (int i = 0; i < stateBitCount; i++)
    {
        int bitmask = 1 << i;
        if ((bitmask & state) == 0)
        {
            stateSet = false;
        }
        else
        {
            if (stateSet)
                return false;
            if (row[i] != '.')
                return false;
            stateSet = true;
        }
    }
    return true;
}

bool isValidStateWithPrevious(int state, int previousState, int stateBitCount)
{
    // State is not valid if:
    // * bit is set in the state
    // * bit is set diagonally in the previous state
    for (int i = 0; i < stateBitCount; i++)
    {
        if (!isBitSet(state, i))
            continue;

        if (i > 0)
        {
            if (isBitSet(previousState, i - 1))
                return false;
        }
        if (i < stateBitCount - 1)
        {
            if (isBitSet(previousState, i + 1))
                return false;
        }
    }
    return true;
}

int countBits(int state, int stateBitCount)
{
    int count = 0;
    for (int i = 0; i < stateBitCount; i++)
    {
        if (isBitSet(state, i))
            count++;
    }
    return count;
}

int maxStudents(vector<vector<char>> seats)
{
    int rows = seats.size();
    int cols = seats[0].size();
    const int MaxRowStates = 1 << cols;

    vector<vector<int>> dp(rows, vector<int>(MaxRowStates, 0));
    // Initialize first row. Student is sitting in each seat of
    // valid state
    for (int state = 0; state < MaxRowStates; state++)
    {
        if (!isValidState(state, seats[0], cols))
            continue;
        dp[0][state] = countBits(state, cols);
    }

    for (int row = 1; row < rows; row++)
    {
        int bestRowResult = 0;
        for (int state = 0; state < MaxRowStates; state++)
        {
            if (!isValidState(state, seats[row], cols))
                continue;

            // For valid state of this row, pick best previous state value.
            int bestPreviousStateValue = 0;
            for (int previousState = 0; previousState < MaxRowStates; previousState++)
            {
                if (!isValidStateWithPrevious(state, previousState, cols))
                    continue;
                bestPreviousStateValue = max(bestPreviousStateValue, dp[row-1][previousState]);
            }
            dp[row][state] = bestPreviousStateValue + countBits(state, cols);
        }
    }

    int result = 0;
    for (int state = 0; state < MaxRowStates; state++)
    {
        if (!isValidState(state, seats[rows - 1], cols))
            continue;
        result = max(result, dp[rows - 1][state]);
    }

    return result;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int row, col;
    cin >> row >> col;

    vector<vector<char>> matrix(row, vector<char>(col, '.'));

    for (int r = 0; r < row; r++)
    {
        for (int c = 0; c < col; c++)
        {
            char v;
            cin >> v;
            matrix[r][c] = v;
        }
    }

    cout << maxStudents(matrix);
}
