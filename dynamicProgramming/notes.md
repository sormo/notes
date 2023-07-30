# Recursion

Find out possibility to solve the problem using smaller sub-problems. Contains solutions to problems using solutions to smaller sub-problems.

* __Recursive case__ - call same function on reduced data to obtain solution to subproblem
* __Base case__ - do not call function and return solution directly

## Example: Factorial

```c++
int factorial(int n)
{
    // base case
    if (n == 0)
        return 1;
    
    // recursive case
    int subproblem = factorial(n - 1);

    // combine
    return n * subproblem;
}
```

First the program moves down to __base case__ . Once reaching the base case it will start moving up (the *function stack*) back to original caller combining the solutions of the smaller problems at each step.

## Example: *Fibonacci*

```c++
int fibonacci(int n)
{
    // base case
    if (n == 0 || n == 1)
        return 1;

    // recursive case
    return fibonacci(n - 2) + fibonacci(n - 1);
}
```

Time complexity is `2^n` . Recursive calls can be thought as a binary tree. Each branch executes up to base cases. There is `2^n` nodes in the tree and depth is `log(n)`.

## Example: *Check whether array is sorted*

```c++
bool is_sorted(const std::vector<int>& array, size_t index = 1)
{
    // base case
    if (index == array.size())
        return true;

    // recursive case
    if (array[index] < array[index - 1])
        return false;
    
    return is_sorted(array, index + 1);
}
```

## Example: *Power function*

```c++
int power(int n, int e)
{
    if (e == 0)
        return 1;
    return n * power(n, e - 1);
}
```

This implementation is linear in time complexity. It is possible to reduce complexity to logarithmic (`log(n)`) by utilizing the following property:

```
a^n = 
       - n is even: (a^(n/2))^2
       - n is odd:  n * (a^((n - 1)/2))^2
```
Simply put we may be halving the input to recursive calls for even numbers by multiplying the results (the squared part).

```c++
int power(int n, int e)
{
    if (e == 0)
        return 1;
    
    // even case
    if (e % 2 == 0)
    {
        int subproblem = power(n, e / 2);
        return subproblem * subproblem;
    }

    // odd case
    int subproblem = power(n, (e - 1) / 2)
    return n * subproblem * subproblem;
}
```

```
2^10 = (2^5)^2
2^5 = 2 * (2^4)
2^4 = (2^2)^2
```

## Example: *Count strings*

Count number of binary strings of length `n` which has no consecutive ones. For example for length 3
```
000 -
001 -
010 -
011 x
100 -
101 -
110 x
111 x
```
There is 5 ways for length of 3.

This can be solved very simply by looking at the problem recursively. We will pick the left-most number and recurse the problem on the positions left.

For example we have following recursion tree:
```
                         _ _ _ _ _
            0 _ _ _ _               1 _ _ _ _
    0 0 _ _ _    0 1 _ _ _      1 0 _ _ _      1 1 _ _ _
```
We can see that the case `1 1 _ _ _` is invalid. That means that if we pick `1` as the left most number we have only one option in next recursion and that is `0`.

So if we have `f(n)` different correct strings of length `n` and
* we fix the left most number to be `0` we may recurse on smaller subproblem of size `f(n-1)`
* we fix the left most number to be `1`, this will force the next number to be `0` (i.e. we can't have `11`) and we should continue with subproblem of size `n-1` (i.e. `f(n-2)`)

Because of this, the recursion is:

```
f(n) = f(n-1) + f(n-2)
```

```c++
int count_strings(int n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return 2;
    return count_strings(n - 1) + count_strings(n - 2);
}
```

## Example: *Tower of Hanoi*

```c++
void tower_of_hanoi(int n, char from, char helper, char to)
{
    if (n == 0)
        return;

    tower_of_hanoi(n - 1, from, to, helper);

    std::cout << from << " -> " << to << "\n";

    tower_of_hanoi(n - 1, helper, from, to);
}
```

Perform 3 steps in the recursion:
* move n - 1 discs from `from` to `to` using `helper` rod
* when we have freed the largest disc on `from` move it to empty `to`
* now the the n - 1 discs that resides on `helper` to `to` using the empty `from`

# Backtracking

Problem types:
* Decision problems - yes/no
* Optimization problems - best solution
* Enumeration problems - all solutions

Backtracking - exploring the search space

## Example: *Finding subsets*

Print all subsets of string.

Example:
`abc` : { `abc`, `ab`, `ac`, `a`, `bc`, `b`, `c`, ``}

We will iterate over the input string and at each step we have two possibilities. Either:
* include the letter at `ith` position
* do not include the letter at `ith` position

In solution below, if we do not increment the `output_idx` we will overwrite it in the next recursion thus, not including it in output string.

```c++
void print_subsets(char* input, int input_idx, char* output, int output_idx)
{
    // base case
    if (input[input_idx] == '\0')
    {
        output[output_idx] = '\0';
        std::cout << output << "\n";
        return;
    }

    // recursive case
    // include i-th letter
    output[output_idx] = input[input_idx];
    find_subsets(input, input_idx + 1, output, output_idx + 1);
    // don't include i-th letter
    find_subsets(input, input_idx + 1, output, output_idx);
}
```

## Example: *N-Queen*

On `N x N` board place `N` chess queens such that none will attack each other.

```c++
using board = std::vector<std::vector<char>>;

bool solve_n_queen(board& board, size_t row)
{
    // base case
    if (row == board.size())
        return true;

    // recursive case
    for (size_t col = 0; col < board[0].size(); col++)
    {
        if (!is_possible_to_place_queen(board, row, col))
            continue;
        
        board[row][col] = 'Q';

        if (solve_n_queen(board, row + 1))
            return true;
        
        board[row][col] = '\0';
    }

    return false;
}
```

Code works by fixing queens on rows one by one, checking with the rows below whether valid configuration can be found.

```c++
bool is_possible_to_place_queen(const board& board, size_t row, size_t col)
{
    // column
    for (int i = 0; i < row; i++)
        if (board[i][col] == 'Q')
            return false;
    // left diagonal
    int i = row, j = col;
    while (i >= 0 && j >= 0)
    {
        if (board[i][j] == 'Q')
            return false;
        i--; j--;
    }
    // right diagonal
    i = row; j = col;
    while (i >= 0 && j < board[0].size())
    {
        if (board[i][j] == 'Q')
            return false;
        i--; j++;
    }
    return true;
}
```

## Example: *Generate brackets*

Write a function to generate all possible n-pairs of balanced parentheses `(` and `)`.

Example:
```
n = 2

()()
(())
```

```c++
void generate(std::vector<char>& brackets, int open, int close, int total)
{
    if (open == total && close == total)
    {
        print_solution(brackets);
        return;
    }
    // we can't have more brackets
    if (open > total || close > total)
        return;
    // discard this recursion branch
    if (close > open)
        return;

    brackets.push_back('(');
    generate(brackets, open + 1, close, total);

    brackets.back() = ')';
    generate(brackets, open, close + 1, total);

    brackets.pop_back();
}
```

Tree pruning - do not go to invalid branches which for sure does not lead to correct position.

## Example: *Sudoku solver*

```c++
bool solve(board& board, int row, int col)
{
    if (col > board[0].size())
        return solve(board, row + 1, 0);
    if (row > board.size())
        return true;

    // skip predefined
    if (board[row][col] != 0)
        solve(board, row, col + 1);

    for (int value = 1; value <= 9; value++)
    {
        if (!is_value_allowed(board, row, col, value))
            continue;
        board[row][col] = value;
        if (solve(board, row, col + 1))
            return true;
        board[row][col] = 0;
    }

    return false;
}
```

## Example: *Hamiltonian path*

Check whether *hamiltonian path* exists in a graph. *Hamiltonian path* is a path in a graph which visits __all__ vertices exactly __once__.

```c++
bool solve(const graph_type& graph, int node, std::vector<bool>& visited, int visited_count)
{
    // base case
    if (visited_count == graph.size())
        return true;

    visited[node] = true;

    for (auto child : graph[node])
    {
        if (visited[child])
            continue;

        if (solve(graph, child, visited, visited_count + 1))
            return true;
    }

    // backtracking - undoing what has been done
    visited[node] = false;

    return false;
}

{
    // check whether there is hamiltonian path if start from node i
    for (int i = 0; i < nodes; i++)
        std::cout << solve(graph, i, visited, 1) << "\n";
}
```

> The most important part is undoing of what has been done in recursion. This is the essence of backtracking.

## Example: *Autobiographical numbers*

Autobiographical number is a number such that the first digit of it counts how many zeroes are there in it, the second digit counts how many ones are there and so on.  

For example, 1210 has 1 zero, 2 ones, 1 two and 0 threes.

```c++
bool verify_number(const std::vector<int>& number, const std::vector<int>& counts)
{
    for (int i = 0; i < number.size(); i++)
    {
        if (number[i] != counts[i])
            return false;
    }
    return true;
}

void solve(int index, std::vector<int>& number, std::vector<int>& counts)
{
    // base case
    if (index == number.size())
    {
        if (verify_number(number, counts))
            print_number(number);
        return;
    }

    // recursive case
    for (int i = 0; i < number.size(); i++)
    {
        number[index] = i;
        counts[i]++;

        solve(index + 1, number, counts);

        // back tracking
        counts[i]--;
        number[index] = -1;
    }
}
```

# Dynamic Programming

* __Form a state__ for example `f(x,y,z)` is state of three variables. For example Fibonacci `f(n)` has state of one variable.
* __Form recursive relation__ for example Fibonacci `f(n) = f(n - 1) + f(n - 2)`
* __Overlapping subproblems__
  * *Tabulation* - remember results in fixed table based on state
  * *Memoisation* - remember results in some map or array

## Memoisation

```c++
int fibonacci(int n)
{
    count++;
    if (n <= 2)
        return 1;
    return fib(n - 1) + fib(n - 2);
}
```

This function is called for `fib(20)` 13529 times.

```c++
int fibonacci(int n)
{
    count++;
    if (n <= 2)
        return 1;
    if (memo[n] != -1)
        return memo[n];
    return memo[n] = fib(n - 1) + fib(n - 2);
}
```

After applying memoisation `fib(20)` is called 37 times.

## Tabulation

```c++
int n = 20;
int fib[n + 1];
fib[1] = fib[2] = 1;

for (int i = 3; i <= n; i++)
    fib[i] = fib[i - 1] + fib[i - 2];
```

## Example: *Print set bits in number*

Print number of `1`s in binary representation of numbers from `1` to `n`.

```c++
for (int i = 1; i <= n; i++)
{
    dp[i] = dp[i/2] + (i & 2);
}
```

If we have some binary number, for example `1011` number of set bits in this number is equal to right-shifted number `101` + 1 because the number is odd. Number is odd if the right-most bit is set (which is in this case). Removing last bit (or right-shifting) is equivalent to dividing by two. Hence the recursive relation

```c++
dp[i] = dp[i/2] + (i % 2);
```

which says that number of bits in `i` us equal to number of bits in number without right most bit `i/2` plus whether right-most bit set (whether it's odd).

# 1D Dynamic Programming Problems

Problems which state is made of only one independent variable.  
For example:
* Fibonacci : `f(n) = f(n - 1) + f(n - 2)`
* Triangular number: (representation of number in form of triangle) : `f(n) = f(n - 1) + n`

## Example: *Managing work*

Each day must be done number of work. Each student must at least each three days do work. You are student manager which assigns work to students. Assign days to yourself which minimizes number of work.

For example input:
```
10
3 2 1 1 2 3 1 3 2 1
```
means that there are 10 days, on first day there is 3 (hours) of work, second day 2 and so on. You mist pick days at in 3 days window such that sum of work is minimized.

```c++
int solve(const std::vector<int>& data, int index)
{
    if (index >= data.size())
        return 0;

    if (memo.count(index))
        return memo[index];

    int ans = std::numeric_limits<int>::max();
    for (int i = 1; i <= 3; i++)
        ans = std::min(ans, data[index] + solve(data, index + i));

    return memo[index] = ans;
}

int solve_start(const std::vector<int>& data)
{
    int ans = std::numeric_limits<int>::max();
    for (int i = 0; i < 3; i++)
        ans = std::min(ans, solve(data, i));
    return ans;
}
```

Here is recursive solution with memoization. Recursive state is index of day we are currently considering and we are maintaining amount of work from right up to this day. In other words we will recurse to base case which is outside to the right and then when going up from recursion we will pick branches with minimum value.  
In the end we need to choose the best starting index, either 0, 1 or 2.

Revisit: in other words I would say we just search through all the possible paths from left to right. The search is done in a manner of recursion tree, i.e. we check all the possibilities when we are at particular index in particular state.

```c++
    std::vector<int> dp(c);
    dp[0] = data[0]; dp[1] = data[1]; dp[2] = data[2];

    for (int i = 3; i < c; i++)
        dp[i] = std::min({ dp[i - 1], dp[i - 2], dp[i - 3] }) + a[i];

    std::cout << std::min({ dp[c - 1], dp[c - 2], dp[c - 3] });
```

Here is tabulation bottom-up approach. Initialize `dp` with first 3 values which are starting days. Then in left-to-right manner fill in remaining days. Each time pick minimum value from previous 3-day window incrementing the value with the work in current day.  
In the end pick the best finish day out the last 3 days in the schedule.

## Example: *Maximizing Revenue*

You can pick numbers from row as revenue but you can't pick 3 consecutive numbers. For example:
```
5 5 5 1 1 1
```
all `5`s can't be taken. We can pick only two `5`s and two `1`s.

```c++
int solve(const std::vector<int>& data, int index, int count)
{
    if (index >= data.size())
        return 0;

    if (count == 2)
    {
        return std::max({ solve(data, index + 1, 0), solve(data, index + 2, 0) });
    }

    return std::max({ solve(data, index + 1, count + 1), solve(data, index + 2, 0) }) + data[index];
}

int solve_start(const std::vector<int>& data)
{
    int ans = std::numeric_limits<int>::min();
    for (int i = 0; i < 2; i++)
        ans = std::max(ans, solve(data, i, 0));
    return ans;
}
```

We are searching through the recursion tree maintaining the state of current index and how many consecutive numbers we have picked right before index. If we have two we can't pick current number otherwise we will pick current number and recurse on next or the after next number.

## Example: *Min steps to reach one*

On input you have number `n`. You can perform three operations on `n`:
* decrease by one `n-1`
* divide by two (if divisible) `n/2`
* divide by three (if divisible) `n/3`

Find minimum number of steps before you reach `1` from `n`.

One thing to note that greedy does not work here. Greedy approach may be. Divide by three while possible, then divide by two while possible and at the end remove ones till `1`.

For example number 10:  
greedy approach: `10/2=5`, `5-1=4`, `4-1=3`, `3-1=2`, `2-1=1` (5 steps)  
optimal approach: `10-1=9`, `9/3=3`, `3/3=1` (3 steps)  

```c++
int solve(int n)
{
    if (n == 1)
        return 0;

    int ans = std::numeric_limits<int>::max();
    if (n % 3 == 0)
        ans = std::min(ans, solve(n/3));
    if (n % 2 == 0)
        ans = std::min(ans, solve(n/2));
    ans = std::min(ans, solve(n - 1));
    ans += 1;

    return ans;
}
```

Memoization is missing. Just recurse to all possibilities, picking the branch which returns minimum.

Here is bottom-up approach:

```c++
int solve(int number)
{
    std::vector<int> dp(number + 1, std::numeric_limits<int>::max());

    dp[0] = dp[1] = 0;

    for (int i = 2; i <= number; i++)
    {
        if (i % 3 == 0)
            dp[i] = std::min(dp[i], dp[i/3] + 1);
        if (i % 2 == 0)
            dp[i] = std::min(dp[i], dp[i/2] + 1);
        dp[i] = std::min(dp[i], dp[i-1] + 1);
    }

    return dp[number];
}
```

## Example: *Alphacode*

Let's map characters to numbers like A=1, B=2, C=3, ..., Z=26 . We may get some string like this: 25114 . Find all the strings which may this number represent. Numbers can be partitioned into different string:  
25114 = 2,5,1,1,4 -> BEAAD  
25114 = 25,11,4 -> YKD  
25114 = 2,5,1,14 -> BEAN  
...  

Recursive relation will be:  
`dp[i] = dp[i+1] + dp[i+2]`  
the number of partitions at `ith` index is equal to number of partitions at `ith + 1` plus the number of partitions at `ith + 2`

Recursion tree:
```
                                  {2,5,1,1,4}

                      B,{5,1,1,4}            Y,{1,1,4}

                  BE,{1,1,4}             YA,{1,4}      YK,{4}

            BEA,{1,4}     BEK,{4}    YAA,{4}   YAN        YKD

       BEAA,{4}  BEAN      BEKD       YAAD

        BEAAD
```

It can be seen that number of ways we can partition the string is the number of leaves.


```c++
int solve(const std::string& number, int index)
{
    // if we are at the last index, it is clear that there is only one way to
    // partition the rest, consider it as a base case
    if (index >= number.size() - 1)
        return 1;

    int ans = 0;

    // if number at current index is not '0' we may pick it to partition
    if (number[index] != '0')
        ans += solve(number, index + 1);

    // if number at current index with the number at next index is in correct
    // range, pick both to partition and recurse
    int with_second = (number[index] - '0') * 10 + (number[index + 1] - '0');
    if (with_second >= 10 && with_second <= 26)
        ans += solve(number, index + 2);

    return ans;
}
```

Bottom-up approach. Here we are adding the number of ways from previous index and if the current and previous number is together valid we add also number of ways second to previous.

Consider following input:
```
99999
```
None of two consecutive numbers form valid number (`99`) so we can form only one string of this (`9` is `I`) `IIIII`. That means we will never get to the second case below and `dp[i] = dp[i-1]`.  
Buf if we make some two digit number there:
```
99199
```
We have also `19` there so there is two valid strings `IIAII` or `IISI`. The `dp[<of 9 after 1>]` will become 2 because of the `is_valid` case.

```c++
bool is_valid(char a, char b)
{
    int number = (a - '0') * 10 + (b - '0');

    return number >= 10 && number <= 26;
}

int solve(const std::string& number)
{
    std::vector<int> dp(number.size(), 0);

    dp[0] = 1;
    dp[1] = is_valid(number[0], number[1]) ? 2 : 1;

    for (int i = 2; i < number.size(); i++)
    {
        dp[i] += dp[i-1];

        if (is_valid(number[i-1], number[i]))
            dp[i] += dp[i-2];
    }

    return dp.back();
}
```

## Example: *Rod cutting*

We have a rod of length `n` and array of prices which represents cost of rod of particular prices. For example:
```
n = 8
prices = [1,3,4,5,7,9,10,11]
```
This means that we want to cut rod of length `8` and price for example a rod of length `2` is `3` . We can cut the rod for example:
{1, 7} (cut it to two pieces of length 1 and 7) and we obtain cost of `1 + 10 = 11`

```c++
int solve(int number, const std::vector<int>& prices)
{
    if (number <= 0)
        return 0;

    int ans = 0;
    for (int i = 1; i <= number; i++)
        ans = std::max(ans, solve(number - i, prices) + prices[i]);

    return ans;
}
```

`i` represents the length of the rod we will cut so we will have rod of this size, so we will add price for it (zero based). Then we will recurse for the rest of the rod.

## Example: *House robber*

You are a robber. You want to rob all the houses on the street. You have list of money you get from each house. Problem is that alarm of each house is connected to house next to it. Robbing two adjacent houses brings the police. Given the money from each house computer maximum earning if no two adjacent houses are robbed.

Solution using two recursive state represented by current index and whether house is robbed or not at current index.

```c++
int solve(const std::vector<int>& prices, int index, bool is_robbed)
{
    if (index >= prices.size())
        return 0;

    int ans = is_robbed ? prices[index] : 0;
    if (is_robbed)
        ans += solve(prices, index + 1, false);
    else
        ans += std::max(solve(prices, index + 1, false), solve2(prices, index + 1, true));

    return ans;
}

// solution is max of either first house is robbed or not
int ans = std::max(solve(prices, 0, true), solve(prices, 0, false));
```

The problem has clearly two dimensional recursive state but can be solved using 1D state:

```c++
int solve(const std::vector<int>& prices, int index)
{
    if (index >= prices.size())
        return 0;

    int ans = 0;
    ans = std::max(ans, solve(prices, index + 2) + prices[index]);
    ans = std::max(ans, solve(prices, index + 1));

    return ans;
}
```

```
dp[i, 0] = max(dp[i+1, 0], dp[i+1,1])                                         // if we don't rob current house, we pick the best alternative of either robbing the next one or not
dp[i, 1] = dp[i+1,0] + prices[i] = max(dp[i+2,0], dp[i+2,1]) + prices[i]      // if we rob the current house, we can only not rob the next one, but we get the price for current

dp[i] = max(dp[i,0], dp[i,1]) = max(dp[i+1], dp[i+2] + prices[i])             // whats the answer if we want rob and not rob the current house
```

## Example: *Palindrome partitioning*

Given string find all partitionings of the string such that all the substrings are palindrome (string of size 1 is trivially palindrome). For example string `aabba` can be partitioned 5 ways:
```
a a b b a
a a bb a
a abba
aa b b a
aa bb a
```

```c++
std::vector<std::vector<std::string>> solve(const std::string& str, int from)
{
    if (from >= str.size())
        return {};

    std::vector<std::vector<std::string>> result;

    for (int to = from; to < str.size(); to++)
    {
        if (is_palindrome(str, from, to))
        {
            auto tmp = solve(str, to + 1);

            auto substr = str.substr(from, to - from + 1);

            for (auto& s : tmp)
                s.insert(std::begin(s), substr);

            if (tmp.empty())
                tmp.push_back({ substr });

            for (auto& s : tmp)
                result.push_back(std::move(s));
        }
    }

    return result;
}
```
`to` is inclusive. Recursive state contains only starting index `from`. In recursion check all substrings in `from` to `to` whether it's palindrome and if so, recurse with new `from` set to `to + 1` (as `to` is inclusive).  
`solve` should return all possible partitioning of string from index `from`. If we reach base case, return empty result (partitioning is valid). Then insert the current palindrome to all the results returned from recursion (i.e. form the correct partitioning of the current recursion) and move the results to final results.  
The mysterious empty check is about the case when we have reached the base case in immediate recursion and the result is empty (but should be valid). In that case the final result should only contain the current palindrome.

## Example: *Tri Tiling*

Count how many ways you can fill `3xn` plate with `2x1` dominoes. Example of one configuration for n = 6:

```
a a e e h h
b c c f f i
b d d g g i
```

We can reuse previous computations to compute number of configurations for current column. Column can be in different states:

```
-  x  -  x  -  x  -  x
-  -  x  x  -  -  x  x
-  -  -  -  x  x  x  x

0  1  2  3  4  5  6  7

- mean empty
x mean occupied
```

There is `2^3` number of states in which column can be and these states are obtained from states of previous column.

### State 0

State `0` of column `i` is equal to full state `7` of column `i-1`

### State 1

State `1` can be obtained from state `6` of column `i-1` by adding single domino

```
        i
x x x O O
x x x x
x x x x
```

### State 2

Obtained from state `5` of column `i-1`

```
        i
x x x x 
x x x O O
x x x x
```

### State 3

Can be obtained in 2 ways. Either by adding single domino to state `7` (full state) or adding two horizontal (!) dominoes to state `4`. We can't count also adding two vertical dominoes.

```
        i
x x x x O
x x x x O
x x x x

        i
x x x O O
x x x O O
x x x x
```

And so on.

```c++
int solve(int n)
{
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(8,0));

    dp[0][7] = 1;
    for (int i = 1; i <= n; i++)
    {
        dp[i][0] += dp[i-1][7];
        dp[i][1] += dp[i-1][6];
        dp[i][2] += dp[i-1][5];
        dp[i][3] += dp[i-1][7];
        dp[i][3] += dp[i-1][4];
        dp[i][4] += dp[i-1][3];
        dp[i][5] += dp[i-1][2];
        dp[i][6] += dp[i-1][7];
        dp[i][6] += dp[i-1][1];
        dp[i][7] += dp[i-1][3];
        dp[i][7] += dp[i-1][6];
        dp[i][7] += dp[i-1][0];
    }
    return dp[n][7];
}
```

# 2D Dynamic Programming Problems

2D dynamic problems has 2 variables in recursive state. 

## Example: *Subset sum*

You are given an `array of numbers` and a `sum` as a number. You should decide whether it's possible to obtain `sum` by summing some subset of `array of numbers`.

For example:  
* array of numbers `[2 7 4 5 19]`
* sum `12`

Result is `yes`

* array of numbers `[2 7 4 5 19]`
* sum `22`

Result is `no`

Recursive solution has two variables `index` and `sum` which represents:
> Is it possible to obtain `sum` by including suffix of numbers from `index` (`[index ...]`)

There are two possibilities. You can either include the number at `index` in the `sum` or exclude. This forms following recursive relation:
* include: `f(index + 1, sum - data[index])`
* exclude: `f(index + 1, sum)`

```c++
bool solve(const std::vector<int>& data, int index, int sum)
{
    if (sum == 0)
        return true;

    if (data[index] > sum)
        return false;

    // include
    if (solve(data, index + 1, sum - data[index]))
        return true;

    // exclude
    return solve(data, index + 1, sum);
}
```

### Tabulation solution

In the bottom-up approach we will not ask whether `sum` can be obtained from some suffix of `array of numbers` but rather we will store information whether `sum` could have been obtained from the numbers up to `index` (prefix).

We will have following formula which will deduce the value for current cell from only previous data:
* include `dp[index][sum] |= dp[index - 1][sum - data[index]]`
* exclude `dp[index][sum] |= dp[index - 1][sum]`

This means that `sum` can be obtained using numbers from 0 to `index` only if 
* `sum - data[index]` can be obtained by including up to `index - 1` numbers (that is we will use number at `index`) or
* `sum` can be already obtained by using only numbers up to `index - 1` (not including this one).

|    |   | | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
| -- | - |-| - | - | - | - | - | - | - | - | - | - | -- | -- | -- |
|    | 0 | | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |
|  2 | 1 | | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |
|  7 | 2 | | 1 | 0 | 1 | 0 | 0 | 0 | 0 | 1 | 0 | 1 | 0  | 0  | 0  |
|  4 | 3 | | 1 | 0 | 1 | 0 | 1 | 0 | 1 | 1 | 0 | 1 | 0  | 1  | 0  |
|  5 | 4 | | 1 | 0 | 1 | 0 | 1 | 1 | 1 | 1 | 0 | 1 | 0  | 1  | 1  |
| 19 | 5 | | 1 | 0 | 1 | 0 | 1 | 1 | 1 | 1 | 0 | 1 | 0  | 1  | 1  |

In the table horizontal is `sum` and vertical is `index` which is in this case one-based. This is to have convenient base case with index 0 which represents empty array.
* if the cell above is set, all the cells below are set (this is `dp[index][sum] |= dp[index - 1][sum]` which means that current sum can be already obtained using numbers up to `index`)
* if the cell one row above and `data[index]` cells to the left is set, current cell is set (this is `dp[index][sum] |= dp[index - 1][sum - data[index]]`, i.e. we are including current `data[index]` in the sum).

The last row gives us answer whether it's possible to create particular `sum` including all the numbers in `array of numbers`. So the final answer is in cell `[5,12]`.

The solution can be easily reconstructed by tracing back from `[5,12]` . It could have been set to true only by the cell above (because 12 - 19 is negative). That means that number `19` is not included in the solution. Cell `[4,12]` couldn't have been set be the cell above so number `5` must be included in solution and we got to cell `[3,12-5]`. This cell is set only from above (because cell `[2,7-4]` is false), that means number `4` is not included and we are at cell `[2,7]` from there we must go to (only way) `[1,0]` and from there `[0,0]`. That means there is only solution. To obtain sum `12` we must include numbers `{5, 7}`.

```c++
bool solve()
{
    bool dp[n + 1][sum + 1];
    dp[0][0] = true;

    for (int j = 1; j <= sum; j++)
        dp[0][j] = false;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j <= sum; j++)
        {
            // exclusion
            dp[i][j] = dp[i - 1][j];

            // inclusion
            if (j - a[i] >= 0)
                dp[i][j] |= dp[i - 1][j - a[i]];
        }
    }
}
```

__Note__:

Here is another subset sum example with numbers explicitly given in `data`:

```c++
void solve(const std::vector<int>& data)
{
    int sum = // <sum the numbers in data>

    std::vector<std::vector<bool>> dp(data.size(), std::vector<bool>(sum + 1, false));
    dp[0][data[0]] = true;

    for (size_t i = 1; i < data.size(); i++)
    {
        for (int32_t s = 0; s <= sum; s++)
        {
            if (dp[i-1][s])
                dp[i][s] = true;

            if (s - data[i] >= 0)
            {
                if (dp[i - 1][s - data[i]])
                    dp[i][s] = true;
            }
        }
    }
}
```


### Memory optimization

Current memory complexity is `data.size * sum` If for example both will be `10^5` it may not be possible to run the program.  There are two possible optimizations.

In the bottom-up approach it can be seen that only previous row (`index - 1`) is being used:

* `dp[index - 1][sum - data[index]]` or `dp[index - 1][sum]`

That means we don't the whole table but only keep two rows swap them each time:

```c++
bool dp[2][sum + 1];

// first row dp[0][j]
// second row dp[1][j]

dp[0][0] = true;

for (int j = 1; j <= sum; j++)
    dp[0][j] = false;

for (int i = 1; i <= n; i++)
{
    for (int j = 0; j <= sum; j++)
    {
        // dp[ith] row is 2nd row
        dp[1][j] = dp[0][j];
        if (j - a[i] >= 0)
            dp[1][j] |= dp[0][j - a[i]];
    }

    // copy 2st row to 0th row
    // for next i calculation
    for (int j = 0; j <= sum; j++)
        dp[0][j] = dp[1][j];
}
```

This will drop the memory complexity to `2*sum` but it is possible to drop it even more to single row.

What we can do is to update the values from right to left overwriting the values in the same row:

```c++
bool dp[sum + 1];

// one row dp[j]

dp[0] = true;

for (int j = 1; j <= sum; j++)
    dp[j] = false;

for (int i = 1; i <= n; i++)
{
    for (int j = sum; j >= 0; j--)
    {
        if (j - a[i] >= 0)
            dp[j] |= dp[j - a[i]];
    }
}
```

## Example: *Subset sum with repeating numbers*

This is slight variation of previous problem `Subset sum`. The only addition to the description is:

> It's possible to use numbers of `array of numbers` multiple times in the `sum`.

The recursive state remains the same. We have `index` for which we are deciding whether number there will be included or excluded from the `sum`. But the recursive relation is now different:
* include: `f(index, sum - data[index])`
* exclude: `f(index + 1, sum)`

We move to another index only with exclude option and we stay at the same index if we are able to use the number in the sum there.

```c++
bool solve(const std::vector<int>& data, int index, int sum)
{
    if (sum == 0)
        return true;

    if (data[index] > sum)
        return false;

    // include
    if (solve(data, index, sum - data[index]))
        return true;

    // exclude
    return solve(data, index + 1, sum);
}
```

## Example: *Modulo sum*

You are given a sequence of numbers `a1`, `a2`, ..., `an`, and a number `m`.

Check if it is possible to choose a non-empty subsequence `a_ij` such that the sum of numbers in this subsequence is divisible by `m`.

```c++
bool solve(const std::vector<int>& data, int div)
{
    // the rows of dp are the numbers from `data`, the cols are remainder after division by `div`
    std::vector<std::vector<bool>> dp(data.size(), std::vector<bool>(div, false));

    // on first row we have available only first number (from `data`) so we will set to true only one col
    // which represents the remainder after division of the first number with `div`
    dp[0][data[0] % div] = true;

    // now consider other numbers
    for (int index = 1; index < data.size(); index++)
    {
        // this is taking only the new number
        dp[index][data[index] % div] = true;

        for (int mod = 0; mod < div; mod++)
        {
            if (dp[index - 1][mod])
            {
                // taking the previous numbers and not taking this one
                dp[index][mod] = true;
                // taking the previous numbers and also taking this one
                dp[index][(data[index] + mod) % div] = true;
            }
        }
    }

    return dp[data.size() - 1][0];
}
```

In the solution we iterate through numbers and we fill the `dp` from up to bottom (rows are numbers from `data` and cols are remainder after division by `div`)

Show the process on example input:
```
data: 1 2 3
div: 5
```

Here is `dp` table initialized to all false.

|    | | 0 | 1 | 2 | 3 | 4 |
| -- |-| - | - | - | - | - |
|  1 | | 0 | 0 | 0 | 0 | 0 |
|  2 | | 0 | 0 | 0 | 0 | 0 |
|  3 | | 0 | 0 | 0 | 0 | 0 |

Manually initialize first row which means we will consider only first number `1`. `1 % 5 = 1` so we will set the remainder 1 in first row.

|    | | 0 | 1 | 2 | 3 | 4 |
| -- |-| - | - | - | - | - |
|  1 | | 0 | 1 | 0 | 0 | 0 |
|  2 | | 0 | 0 | 0 | 0 | 0 |
|  3 | | 0 | 0 | 0 | 0 | 0 |

Now we go to second row, which means we are considering number `1` and `2`. First we will set the remainder `2 % 5 = 2` which represents considering only the current number.

|    | | 0 | 1 | 2 | 3 | 4 |
| -- |-| - | - | - | - | - |
|  1 | | 0 | 1 | 0 | 0 | 0 |
|  2 | | 0 | 0 | 1 | 0 | 0 |
|  3 | | 0 | 0 | 0 | 0 | 0 |

Then we will take the remainders which are set in the previous row and for each we will:
* set the same remainder also in current number (excluding current number)
* set the remainder obtained through `(data[index] + mod) % div` (including current number) (in this case it is `(2 + 1) % 5 = 3`)

|    | | 0 | 1 | 2 | 3 | 4 |
| -- |-| - | - | - | - | - |
|  1 | | 0 | 1 | 0 | 0 | 0 |
|  2 | | 0 | 1 | 1 | 1 | 0 |
|  3 | | 0 | 0 | 0 | 0 | 0 |

Same process we will repeat for the number `3`

|    | | 0 | 1 | 2 | 3 | 4 |
| -- |-| - | - | - | - | - |
|  1 | | 0 | 1 | 0 | 0 | 0 |
|  2 | | 0 | 1 | 1 | 1 | 0 |
|  3 | | 1 | 1 | 1 | 1 | 1 |

If any cell in first column is set, this means we are able to create subset sum which is divisible by `div`.

## Example: *Partition Equal Subset Sum*

Given an integer array `nums`, return `true` if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or `false` otherwise.

```
Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
```

```
Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
```

[Leetcode](https://leetcode.com/problems/partition-equal-subset-sum/)

```c++
bool solve_tab(const std::vector<int>& data)
{
    // compute the sum of the elements
    int32_t sum = 0;
    for (auto n : data)
        sum += n;

    // if the sum is not even, for sure we can't partition it into equal sum subsets
    if (sum % 2 != 0)
        return false;

    // now create dp row represent number of elements included and columns are sums
    // dp[i,j] = is it possible to obtain sum j using first i elements of array ?
    std::vector<std::vector<bool>> dp(data.size(), std::vector<bool>(sum + 1, false));
    // first row represents available sums using first element, it's obviously only that element
    dp[0][data[0]] = true;

    for (size_t i = 1; i < data.size(); i++)
    {
        for (int32_t s = 0; s <= sum; s++)
        {
            // inherit value from previous row
            if (dp[i-1][s])
                dp[i][s] = true;

            if (s - data[i] >= 0)
            {
                // check if sum "s - data[i]" is available using previous numbers
                if (dp[i - 1][s - data[i]])
                    dp[i][s] = true;
            }
        }
    }

    return dp[data.size() - 1][sum / 2];
}
```

This is really a subset sum problem. At the end we only check whether it's possible to obtain `sum/2`. Thats all.

# Knapsack Problem

## 0/1 Knapsack

In a knapsack problem you have list of elements and a knapsack with `capacity`. Each element has two properties `size` and `value`. You need to pick subset of elements. The sum of `size`s in the subset is smaller or equal to `capacity` and the sum of `value`s is maximized.

---
__Example__ :

```
capacity : 4

element idx : 0 1 2 3 4
size        : 1 2 3 2 2
value       : 8 4 0 5 3
```

For example we can pick to knapsack elements 3 and 4. We will fill the capacity (because sizes are 2 + 2) and total value we will obtain is 8 (5 + 3).  
This is not optimal solution. For example picking elements 0 and 3 will lead to total value of 13.

__Note__ :  
The __greedy approach__ may be:
> Sort the elements by the ratio of `value/size` and pick only the elements with highest ratio.  

This approach may work in some cases but not always. For example:

```
capacity : 4

element idx : 0  1   2
size        : 3  2   2
value       : 30 15  18
size/value  : 10 7.5 9
```

Using the greedy approach we will pick only the first element with ration 10, but the optimal solution is picking the two elements with lower ratio.

---

This problem is very similar to __subset-sum__ . We need to pick a subset i.e. for each element we need to decide whether we will pick it or not.

The recursive relation is following, given:

```
i: current index (in this case we are considering suffix from right to left)
c: current capacity

f(i, c) = max(f(i - 1, c - size[i]) + value[i], f(i - 1, c))
                include element                    exclude

note: we can include element only if c - size[i] >= 0
```

So considering the element `i` we will recurse to two branches each time considering the next element and either picking the value and lowering the capacity (*include*) or doing nothing (*exclude*). We pick the best option.

```c++
int knapsack(std::vector<element>& data, int index, int capacity)
{
    if (index < 0 || capacity == 0)
        return 0;

    int result = knapsack(data, index - 1, capacity);

    if (capacity - data[index].size >= 0)
        result = std::max(result, knapsack(data, index - 1, capacity - data[index].size) + data[index].value);

    return result;
}
```

Adding memoization should be simple. There is two states `index` and `capacity`.

Tabular solution:

```c++
    // table with rows: index, columns: capacity
    // data has first empty index (elements start at index 1)
    std::vector<std::vector<int>> dp(data.size(), std::vector<int>(capacity + 1, 0));

    for (int i = 1; i < data.size(); i++)
    {
        for (int c = 1; c <= capacity; c++)
        {
            dp[i][c] = dp[i - 1][c];
            if (c - data[i].size >= 0)
                dp[i][c] = std::max(dp[i][c], dp[i - 1][c - data[i].size] + data[i].value);
        }
    }

    return dp[data.size() - 1][capacity];
```

## 0/N Knapsack

The only difference from 0/1 knapsack problem is:

> Elements can be included in knapsack infinite number of times i.e. we have at hand infinite number of items of each type.

Modification to recursive is simple:

```c++
    if (index < 0 || capacity == 0)
        return 0;

    int result = knapsack(data, index - 1, capacity);

    if (capacity - data[index].size >= 0)
        result = std::max(result, knapsack(data, index, capacity - data[index].size) + data[index].value);

    return result;
```

If we include the element, we will stay on the same index. As a result we may include the current element __arbitrary number of times__.

TODO tabular 0/N knapsack

## Colorful Knapsack

In this problem we have:
* `N` number of elements
* `M` number of colors
* `X` capacity of knapsack
* `W[i]` weight of element `i`
* `C[i]` color of element `i`

Pick subset of elements of size exactly `M` such that sum of weights is less or equal to capacity `X` and there is exactly one of each color. 

---

Example:

```
number of elements (N)   : 8
number of colors (M)     : 3
capacity of knapsack (X) : 10
weights (W)              : { 2, 3, 4, 2, 4, 5, 2, 3 }
colors (M)               : { 1, 1, 1, 2, 2, 2, 3, 3 }
```

So we need to pick 3 elements of each color which will maximize the weight such that weight is <= 10.

We can use tabular approach with two dimensional boolean dp table where rows will be colors and columns the weight:

|    | | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| -- |-| - | - | - | - | - | - | - | - | - | - | -  |
|  1 | | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  |
|  2 | | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  |
|  3 | | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  |

Cell `dp[i][j]` will represent __whether it's possible to obtain weight `j` using up to colors `i`.__

To fill in the first row:

|    | | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| -- |-| - | - | - | - | - | - | - | - | - | - | -  |
|  1 | | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0  |
|  2 | | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  |
|  3 | | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  |

Using only the color `1` we can obtain weight `2`, `3` and `4`.

To fill the second row:

|    | | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| -- |-| - | - | - | - | - | - | - | - | - | - | -  |
|  1 | | 0 | 0 | 1 | 1 | 1 | 0 | 0 | 0 | 0 | 0 | 0  |
|  2 | | 0 | 0 | 0 | 0 | 1 | 1 | 1 | 1 | 1 | 1 | 0  |
|  3 | | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  |

If we are using only the first two colors we can pick for example for color `1` weight of `2` (the first element) and then for color `2` the weight `2` (this is the fourth element). This means that weight `2+2` is possible using the first two colors.  
The same way weight `5` can be obtained using the second element with color `1` with weight `3` and fourth element with color `2` and weight `2`.

We can see that the current cell can be set if the cell in the previous row is set minus the weights of the current colors.

```
for k in current colors
    dp[i][j] = dp[i - 1][j - W[k]]
```

Seems complicated but we just iterate over weights of current color and check whether cell at previous row with color minus current color is set.

```c++
int solve(std::vector<element>& data, int capacity, int colors)
{
    // create a map color -> available element indices
    std::vector<std::vector<int>> color_map(colors + 1, std::vector<int>());
    for (int i = 0; i < data.size(); i++)
        color_map[data[i].color].push_back(i);

    std::vector<std::vector<bool>> dp(colors + 1, std::vector<bool>(capacity + 1, false));

    // initialize first row -> available capacities using only first color
    for (auto w : color_map[1])
        dp[1][w] = true;

    for (int c = 2; c <= colors; c++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            // iterate over elements of current color
            for (auto i : color_map[c])
            {
                if (w - data[i].size < 0)
                    continue;
                
                // if the cell is set on one less color
                if (dp[c - 1][w - data[i].size])
                    dp[c][w] = true;
            }
        }
    }

    // get the highest weight in the last row
    for (auto i = capacity; i >= 0; i--)
    {
        if (dp[colors][i])
            return i;
    }

    return -1;
}
```

# 2D DP Problems

## Paint House

This problem is similar to `House Robber`. We have array of houses and 3 colors `red`, `green` and `blue`. We know also how much money costs to paint each house with each color (2D array, see example). Minimize the cost of painting all the houses with restriction that no two houses can be painted with same color:

### Example

|        | | 0  | 1  | 2  |
| ------ |-| -- | -- | -- |
|  red   | | 14 | 11 | 14 |
|  green | | 11 |  5 | 10 |
|  blue  | |  2 | 14 |  3 |

We have 3 houses. To paint for example house `1` with color `green` costs `5`.

Here the greedy works but example where it doesn't work is easy:

|        | | 0 | 1    |
| ------ |-| - | ---- |
|  red   | | 1 | 1    |
|  green | | 2 | 1000 |

In greedy we would pick the `1` in first column and this will force us to take `1000` in second. But optimal is ofc `2` in first and `1` in second.

### Solution

We will create `dp` where each cell represents 

> minimum cost of painting house with color c including first i houses

|        | | 0 | 1 | 2 |
| ------ |-| - | - | - |
|  red   | | 0 | 0 | 0 |
|  green | | 0 | 0 | 0 |
|  blue  | | 0 | 0 | 0 |

Minimum cost for painting first house is just the price painting it:

|        | |  0 | 1 | 2 |
| ------ |-| -- | - | - |
|  red   | | 14 | 0 | 0 |
|  green | | 11 | 0 | 0 |
|  blue  | |  2 | 0 | 0 |

Now painting the second (`1`) house with `red` color means that the first (`0`) house could have been painted with `green` or `blue`. That means that we will paint the price of painting it red (ofc) plus the min of painting the previous house with `green` or `blue`. That is

painting 1 red = 11 + min{11, 2} = 13

|        | |  0 | 1  | 2 |
| ------ |-| -- | -- | - |
|  red   | | 14 | 13 | 0 |
|  green | | 11 | 0  | 0 |
|  blue  | |  2 | 0  | 0 |

Similarly  
painting 1 green = 5 + min{14, 2} = 7  
painting 1 blue = 14 + min{14, 11} = 25

|        | |  0 | 1  | 2 |
| ------ |-| -- | -- | - |
|  red   | | 14 | 13 | 0 |
|  green | | 11 | 7  | 0 |
|  blue  | |  2 | 25 | 0 |

We can come up with recursive relation:

```
dp(i,j) = minimum cost of H(...i) if ith house is painted with jth color
dp(i,j) = min{dp(i-1,j')} where j' != j (all but j)
```

```c++
int solve(const std::vector<std::vector<int>>& data, int colors, int houses)
{
    std::vector<std::vector<int>> dp(colors, std::vector<int>(houses, 0));

    for (int c = 0; c < colors; c++)
        dp[c][0] = data[c][0];

    for (int h = 1; h < houses; h++)
    {
        for (int c = 0; c < colors; c++)
        {
            // find the minimum value of painting previous houses excluding this color
            int min_prev = std::numeric_limits<int>::max();
            for (int c2 = 0; c2 < colors; c2++)
            {
                if (c2 == c)
                    continue;
                min_prev = std::min(min_prev, dp[c2][h-1]);
            }
            // assign the dp
            dp[c][h] = min_prev + data[c][h];
        }
    }

    // result is the minimum of painting last house
    int result = std::numeric_limits<int>::max();
    for (int c = 0; c < colors; c++)
        result = std::min(result, dp[c][houses-1]);

    return result;
}
```

One variation of the problem is to increase the number of colors to `K`. The complexity is `O(houses * colors * colors)` but this can be reduced to `O(houses * colors)` . The second iteration over colors is needed only because we want the minimum from previous column without including the current color.
The way how to optimize this iteration it to keep two minimums (`min1` and `min2`) for each column. The smallest number and the second smallest number. Then if we want a minimum from column not including the current color we just simply check whether the value in previous color is `min1` and if so we take `min2`

```c++
if (dp[color][house - 1] == min1)
    dp[color][house] = min2 + cost[color][house];
else
    dp[color][house] = min1 + cost[color][house];
```

```c++
void maintain_minimums(int& min1, int& min2, int new_value)
{
    if (new_value < min1)
    {
        min2 = min1;
        min1 = new_value;
    }
    else if (new_value < min2)
    {
        min2 = new_value;
    }
}

int solve(const std::vector<std::vector<int>>& data, int colors, int houses)
{
    std::vector<std::vector<int>> dp(colors, std::vector<int>(houses, 0));

    int min1_prev = std::numeric_limits<int>::max();
    int min2_prev = std::numeric_limits<int>::max();

    for (int c = 0; c < colors; c++)
    {
        dp[c][0] = data[c][0];
        maintain_minimums(min1_prev, min2_prev, dp[c][0]);
    }

    for (int h = 1; h < houses; h++)
    {
        int min1_cur = std::numeric_limits<int>::max();
        int min2_cur = std::numeric_limits<int>::max();

        for (int c = 0; c < colors; c++)
        {
            if (dp[c][h-1] == min1_prev)
                dp[c][h] = min2_prev + data[c][h];
            else
                dp[c][h] = min1_prev + data[c][h];

            maintain_minimums(min1_cur, min2_cur, dp[c][h]);
        }
        
        min1_prev = min1_cur;
        min2_prev = min2_cur;
    }

    // result is the minimum of painting last house
    int result = std::numeric_limits<int>::max();
    for (int c = 0; c < colors; c++)
        result = std::min(result, dp[c][houses-1]);

    return result;
}
```

## Make The Fence Great Again

In this problem you have a fence made of boards. Each board has height `height[i]`. The fence is great if there are not two adjacent boards with same height. You can increase the height of a board by one but you will pay price `price[i]`. Find the minimum amount of money to make the fence great.

### Example

We have a fence with three boards like this:

```
height = { 2 2 3 }
price  = { 4 1 5 } 
```

What we can do is to increase the height of the middle board and pay price `1`. We will get to following situation:

```
height = { 2 3 3 }
price  = { 4 1 5 } 
```

Now we can increase the height of the middle board again to get to:

```
height = { 2 4 3 }
price  = { 4 1 5 } 
```

This is the optimal solution in this case by paying the total price of `2`. We may have also increased the first board at the beginning leading to great fence `{ 3 2 3 }` but for the price of `4`.

### Solution

__Greedy__

Greedy does not work here. It should be evident that always picking the cheapest board may not lead to optimal solution (TODO some example)

__Maximum number of increases__

One should realize that there is no point increasing any board more than twice. If any board has been increased three times or more this will never lead to optimal solution (TODO elaborate)

This problem is the same as previous *House painting* problem. We will create a `dp` where rows will be number of increases of board and columns will be boards:

```
dp(i, j) = minimum price if all the boards up to and including j are great and the current board is increased i times
```

|    | | 0 | 1 | 2 |
| -- |-| - | - | - |
|  0 | | 0 | 0 | 0 |
|  1 | | 0 | 0 | 0 |
|  2 | | 0 | 0 | 0 |

We will pre-fill the first column according the prices (from example)

|    | | 0 | 1 | 2 |
| -- |-| - | - | - |
|  0 | | 0 | 0 | 0 |
|  1 | | 4 | 0 | 0 |
|  2 | | 8 | 0 | 0 |

Now we will iterate over the second column and we will pick each time minimum value from previous column but __excluding the cell with same height as current cell__. 

For example cell at `[1,0]` has height `2 + 0` (height of the second board increased 0 times). So now we will check the previous row and we will exclude cells with same height. That is the cell `[0,0]` (it's the height of first board increased 0 times which is also 0). So for this cell we will pick `min(4, 8)`

|    | | 0 | 1 | 2 |
| -- |-| - | - | - |
|  0 | | 0 | 4 | 0 |
|  1 | | 4 | 0 | 0 |
|  2 | | 8 | 0 | 0 |

The second cell at `[1,1]` has height `2 + 1` (height of the second board increased 0 times). So we can't pick `4` from the first column resulting in `min(0, 8) + 2`

|    | | 0 | 1 | 2 |
| -- |-| - | - | - |
|  0 | | 0 | 4 | 0 |
|  1 | | 4 | 2 | 0 |
|  2 | | 8 | 4 | 0 |

And the last cell is `min(0,4) + 4`. That is we can't consider cell `[0,2]` because it has same height and also we need to increase the current board two times (paying `2*2`).

Here is the solution:

```c++
int64_t solve_tab(std::vector<board>& data)
{
    std::vector<std::vector<int64_t>> dp(3, std::vector<int64_t>(data.size(), 0));

    for (size_t i = 0; i < 3; i++)
        dp[i][0] = data[0].price * i;

    for (size_t b = 1; b < data.size(); b++)
    {
        for (size_t s = 0; s < 3; s++)
        {
            int64_t min_prev = std::numeric_limits<int64_t>::max();
            for (size_t s2 = 0; s2 < 3; s2++)
            {
                if (data[b].size + s == data[b - 1].size + s2)
                    continue;
                min_prev = std::min(min_prev, dp[s2][b - 1]);
            }
            dp[s][b] = min_prev + s * data[b].price;
        }
    }

    int64_t result = std::numeric_limits<int64_t>::max();
    for (size_t s = 0; s < 3; s++)
        result = std::min(result, dp[s][data.size() - 1]);

    return result;
}
```

We can also pre-compute the prices and sizes. This code is more straight forward but it has much bigger memory consumption:

```c++
int64_t solve_tab(std::vector<board>& data)
{
    std::vector<std::vector<int64_t>> size(3, std::vector<int64_t>(data.size(), 0));
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < data.size(); j++)
            size[i][j] = data[j].size + i;

    std::vector<std::vector<int64_t>> price(3, std::vector<int64_t>(data.size(), 0));
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < data.size(); j++)
            price[i][j] = data[j].price * i;

    std::vector<std::vector<int64_t>> dp(3, std::vector<int64_t>(data.size(), 0));
    for (size_t i = 0; i < 3; i++)
        dp[i][0] = data[0].price * i;

    for (size_t b = 1; b < data.size(); b++)
    {
        for (size_t s = 0; s < 3; s++)
        {
            int64_t min_prev = std::numeric_limits<int64_t>::max();
            for (size_t s2 = 0; s2 < 3; s2++)
            {
                if (size[s][b] == size[s2][b - 1])
                    continue;
                min_prev = std::min(min_prev, dp[s2][b - 1]);
            }
            dp[s][b] = min_prev + price[s][b];
        }
    }

    int64_t result = std::numeric_limits<int64_t>::max();
    for (size_t s = 0; s < 3; s++)
        result = std::min(result, dp[s][data.size() - 1]);

    return result;
}
```

## Best Time to Buy and Sell Stock

Problem from [leetcode](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/)

You are given an integer array `prices` where `prices[i]` is the price of a given stock on the ith day, and an integer `k`.

Find the maximum profit you can achieve. You may complete at most `k` transactions.

```c++
int solve_rec(int current_price, bool is_buy, int available_transactions, std::vector<int>& prices)
{
    if (current_price == prices.size())
        return 0;

    // do nothing
    int result = solve_rec(current_price + 1, is_buy, available_transactions, prices);

    if (available_transactions == 0)
        return 0;

    // either buy or sell
    if (is_buy)
        result = std::max(result, -prices[current_price] + solve_rec(current_price + 1, false, available_transactions, prices));
    else
        result = std::max(result, +prices[current_price] + solve_rec(current_price + 1, true, available_transactions - 1, prices));

    return result;
}

int solve(std::vector<int>& prices, int total_transactions)
{
    return solve_rec(0, true, total_transactions, prices);
}
```

```c++
int solve_tab(int transactions, std::vector<int>& prices)
{
    int days = prices.size();
    
    std::vector<std::vector<int>> dp(transactions + 1, std::vector<int>(days, 0));

    for (int t = 1; t <= transactions; t++)
    {
        for (int d = 1; d < days; d++)
        {
            // max profit of selling at this day
            int max_profit = 0;
            // iterate over days up to this day and check what profit we could obtain
            // if we have bought at that day ( - prices[k] ) and sell today ( + prices[d] )
            for (int k = 0; k < d; k++)
            {
                max_profit = std::max(prices[d] - prices[k] + dp[t - 1][k], max_profit);
            }

            // the other case is to do nothing at this day (just copy profit from previous day)
            dp[t][d] = std::max(dp[t][d - 1], max_profit);
        }
    }

    return dp[transactions][days - 1];
}
```

# Partition Problems

## Plates

In this problem you have stack of plates. Like this stacked horizontally:

```
||||||||
||||||||
||||||||
```

Here we have three stacks each containing 8 plates. We can pick plates from the left. For example we can pick 3 plates from first stack and two plates from last stack (`p` means it was picked)

```
ppp|||||
||||||||
pp||||||
```

We can't just pick any plate, only plates from the left.

Each plate has `value` number assigned to it. We need to pick exactly `K` plates maximizing the sum of `value`s of the picked plates.

### Example

We have following plates (given `value`) and we need to pick `5`:

```
10 10 100 30
80 50  10 50
```

One solution may be to pick all the plates from the first stack and single plate from the second leading to total value `230`.

Optimal solution is to pick three plates from the first stack and two plates from second leading to total value of `250`

### Solution

If we can only pick all plates from the left we may preprocess the value table as follows (from example):

```
10  20 120 150
80 130 140 190 
```

This way we know that if we pick for example three plates from first stack we will obtain 120 value for this stack.

`DP` table will look as follows:

|    | | 0 | 1 | 2 | 3 | 4 | 5 |
| -- |-| - | - | - | - | - | - |
|  0 | | 0 | 0 | 0 | 0 | 0 | 0 |
|  1 | | 0 | 0 | 0 | 0 | 0 | 0 |

* `row[i]` represents __included stacks up to i-th row of stacks__
* `column[j]` represents __picking j plates from the plate row i__ 

Filling in the first row:

* `dp[0][0]` is 0, because it means picking 0 plates including the first stack
* `dp[0][1]` is 10, it means picking one plate from the first stack
* ...

|    | | 0 |  1 |  2 |   3 |   4 | 5 |
| -- |-| - |  - |  - |   - |   - | - |
|  0 | | 0 | 10 | 20 | 120 | 150 | 0 |
|  1 | | 0 |  0 |  0 |   0 |   0 | 0 |

We can't pick 5 plates using the first stack only, so the value is left zero.

Filling the second row:

* `do[1][0]` is again 0, because it means picking zero plates including the first two stacks
* `dp[1][1]` is 80. We need to pick one plate including first two stacks. That means either plate with value `10` (first stack) or plate with value `80` (second stack).
* `dp[1][2]` is 130. Here we have three choices to pick two plates:
* * __2, 0__ pick both plates from first stack, that is `20`
* * __1, 1__ pick one plate from first stack and one plate from second, that is `10 + 80 = 90`
* * __0, 2__ pick both plates from second stack, that is `130`
* `dp[1][3]` is 140
* * __3, 0__ `120` (all from first stack)
* * __2, 1__ `20 + 80 = 100`
* * __1, 2__ `10 + 130 = 140`
* * __0, 3__ `140`
* `dp[1][4]` is 200
* * __4, 0__ `150`
* * __3, 1__ `120 + 80 = 200`
* * __2, 2__ `20 + 130 = 150`
* * __1, 3__ `10 + 140 = 150`
* * __0, 4__ `190`
* `dp[1][5]` is 250
* * __5, 0__ can't be
* * __4, 1__ `150 + 80 = 230`
* * __3, 2__ `120 + 130 = 250`
* * __2, 3__ `20 + 140 = 160`
* * __1, 4__ `10 + 190 = 200`
* * __0, 5__ can't be

|    | | 0 |  1 |   2 |   3 |   4 |   5 |
| -- |-| - |  - |   - |   - |   - |   - |
|  0 | | 0 | 10 | 20  | 120 | 150 |   0 |
|  1 | | 0 | 80 | 130 | 140 | 200 | 250 |

```c++
int32_t solve(vector2d<int32_t>& data, int32_t take_count)
{
    vector2d<int32_t> dp(data.size(), std::vector<int32_t>(take_count + 1));

    // preprocess data
    for (int32_t r = 0; r < data.size(); r++)
        for (int32_t c = 1; c < data[r].size(); c++)
            data[r][c] += data[r][c - 1];

    // fill in the first row
    for (int32_t c = 1; c < dp[0].size(); c++)
        dp[0][c] = c - 1 < data[0].size() ? data[0][c - 1] : 0;

    // r is how many stacks we include
    // c is how many plates we need to tak
    // t is how many plates we will take from current row
    for (int32_t r = 1; r < dp.size(); r++)
    {
        for (int32_t c = 1; c < dp[r].size(); c++)
        {
            for (int32_t t = 0; t <= c; t++)
            {
                int32_t take_from_current = t > 0 && t <= data[r].size() ? data[r][t - 1] : 0;

                dp[r][c] = std::max(dp[r][c], take_from_current + dp[r - 1][c - t]);
            }
        }
    }

    return dp[dp.size()-1].back();
}
```

```c++
int32_t solve_rec_fnc(int32_t taken_so_far, int32_t row, const vector2d<int32_t>& data, int32_t to_take)
{
    if (taken_so_far > to_take)
        return 0;

    if (row >= data.size())
        return 0;

    int32_t result = solve_rec_fnc(taken_so_far, row + 1, data, to_take);
    for (int32_t i = 1; i <= data[row].size(); i++)
    {
        if (taken_so_far + i > to_take)
            break;
        result = std::max(result, solve_rec_fnc(taken_so_far + i, row + 1, data, to_take) + data[row][i - 1]);
    }

    return result;
}
```

## Partition Array for Maximum Sum

[Leetcode](https://leetcode.com/problems/partition-array-for-maximum-sum/)

Given an integer array `arr`, partition the array into (contiguous) subarrays of length at most `k`. After partitioning, each subarray has their values changed to become the maximum value of that subarray.

Return the largest sum of the given array after partitioning. Test cases are generated so that the answer fits in a 32-bit integer.

Example:
```
Input: arr = [1,15,7,9,2,5,10], k = 3
Output: 84
Explanation: arr becomes [15,15,15,9,10,10,10]
```

```c++
// what is the maximum value when we partition suffix of data from index ?
int solve_rec(int index, std::vector<int>& data, int k)
{
    if (index >= data.size())
        return 0;

    if (memo.count(index))
        return memo[index];

    int result = 0;
    int max_so_far = 0;
    for (int i = 0; i < k; i++)
    {
        if (index + i == data.size())
            break;
        max_so_far = std::max(max_so_far, data[index + i]);
        result = std::max(result, solve_rec(index + i + 1, data, k) + (i + 1) * max_so_far);
    }

    return memo[index] = result;
}
```

## Split Array Largest Sum

[LeetCode](Split Array Largest Sum)

Given an integer array `nums` and an integer `k`, split `nums` into `k` non-empty subarrays such that the largest sum of any subarray is minimized.

Return the minimized largest sum of the split.

A subarray is a __contiguous__ part of the array.

Example:
```
Input: nums = [7,2,5,10,8], k = 2
Output: 18
Explanation: There are four ways to split nums into two subarrays.
The best way is to split it into [7,2,5] and [10,8], where the largest sum among the two subarrays is only 18.
```

```c++
    // what is the minimum of max subarray sums if we split k times the rest of nums from index
    int splitArrayRec(int index, std::vector<int>& nums, int k)
    {
        // base case
        if (index == nums.size())
        {
            if (k == 0)
                return 0;
            return std::numeric_limits<int>::max();
        }

        // invalid
        if (k <= 0)
            return std::numeric_limits<int>::max();

        int result = std::numeric_limits<int>::max();
        int sum_so_far = 0;
        for (int i = index; i < nums.size(); i++)
        {
            sum_so_far += nums[i];
            int max_sum = std::max(sum_so_far, splitArrayRec(i + 1, nums, k - 1));
            result = std::min(result, max_sum);
        }

        return result;
    }
```

# Combinatorics and Dynamic Programming

## Tiling Problem I

Given a `2 x n` board and tiles of size `2 x 1`, count the number of ways to tile the given board using tiles. A tile can be placed horizontally or vertically.

### Example

```
Board with single column, there is only one way, place single tile vertically:
a
a
```
```
Board with two columns, there are two way, place two tiles vertically or horizontally:
ab   aa
ab , bb
```
```
Board with three columns, there are three ways:
abc   abb   aac
abc , acc , bbc
```

### Solution

We should use dynamic programming __fill single column and count number of ways of tiling the rest of the board__.

For example wa have board of length 8:

```
xxxxxxxx
xxxxxxxx
```

How many ways we can fill first column ? There are two ways:
```
axxxxxxx , aaxxxxxx
axxxxxxx , bbxxxxxx
```

The second way will fill also the second column but as long as the first column is filled we are ok.

From that the recursive relation is clear:

> f(n) = f(n - 1) + f(n - 2)

(each time we will recurse on the rest of the board `x`s)

## Tiling Problem II

Same as the `Tiling Problem I` only that we have one more tile available. That is `2 x 2`

So we have:

```
aa , a , aa
     a   aa
```

How will the recursive relation change? Just think about how to fill the single column. So there is one more way and that is placing single `2 x 2` tile. This means we need to recurse on `f(n - 2)` one more time:

> f(n) = f(n - 1) + f(n - 2) + f(n - 2)

## Tiling Problem III

Same as the `Tiling Problem I` only that we have one more tile available - a L-shape tile:

```
aa , a  
     aa
```

(the tiles can be rotated in any way, not drawing all the possibilities)

### Solution

Always think about filling left most column. As previous we can fill in two ways first column using `aa` tile (see `Tiling Problem I`)

> f(n) = f(n - 1) + f(n - 2) + 

If we use the L-shape we get to situation where column is only partially filled:

```
axxxxxxx  or  aaxxxxxx
aaxxxxxx      axxxxxxx
```

We will introduce two new functions:

> g(n) -> represents the number of ways to fill 2 x n board with one additional tile in top-left
> h(n) -> represents the number of ways to fill 2 x n board with one additional tile in bottom-left

```
axxxxxxxxx  or  aaxxxxxxxx
aaxxxxxxxx      axxxxxxxxx
  <- n  ->        <-  n ->
g(n)            h(n)
```

> Column of the extra tile is not included in n !

So the whole recursive relation is

> f(n) = f(n - 1) + f(n - 2) + g(n) + h(n)

Now one simplification is that (it's only flipped but the number of ways is the same)

> g(n) = h(n)

In this situation

```
xxxxxxxxx
 xxxxxxxx
 <- n  ->
```

What is the number of ways to fill left-most column ?

```
aaxxxxxxx or aaxxxxxxx
 xxxxxxxx     axxxxxxx
 <- n  ->     <- n  ->
```

> h(n) = g(n - 1) + f(n - 1)

or

> g(n) = h(n - 1) + f(n - 1)

The base-cases are:
```
f(1) = 1, f(2) = 2
g(1) = 1, g(2) = 2
```

```c++
int solve(int n)
{
    std::vector<int> f(n + 1), g(n + 1);
    f[1] = g[1] = 1;
    f[2] = g[2] = 2;

    for (int i = 3; i <= n; i++)
    {
        f[i] = f[i - 1] + f[i - 2] + 2 * g[i - 2];
        g[i] = g[i - 1] + f[i - 1];
    }

    return f[n];
}
```

## M3TILE Spoj

Count number of ways we can tile the 3xn board with 2x1 dominoes. This is the same problem already solved in *Tri Tiling*

We have 3xn board:
```
xxxxxxx
xxxxxxx
xxxxxxx
```

and  we are placing 2x1 dominoes rotated horizontally or vertically:
```
aaxxxxx
bxxxxxx
bccxxxx
```

### Solution

We need to always think about filling in the left-most column. We have following possibilities:

```
axxxxxx    aaxxxxx    aaxxxxx
axxxxxx ,  bxxxxxx ,  bbxxxxx
bbxxxxx    bxxxxxx    ccxxxxx
```

> f(n) = g(n-2) + h(n-2) + f(n-2)

where

> g(n) -> represents the number of ways to fill 3 x n board with two additional tiles in top-left
> h(n) -> represents the number of ways to fill 3 x n board with two additional tiles in bottom-left

One thing to note is that again two additional tiles does not count to n:

```
axxxxxx
axxxxxx
bbxxxxx
  <-n->
```

Now we define `g(n)`, we have two possibilities:

```
xxxxxx      axxxxx    bbxxxx
xxxxxx  ->  axxxxx ,  ccxxxx
 xxxxx       xxxxx     xxxxx
 <-n->
```

g(n) = f(n) + i(n - 1)

where

> i(n) -> represents the number of ways to fill 3 x n board with one additional tile in bottom-left

Now we define `i(n)`, we have only one possibility:

```
 xxxxx      xxxxx
 xxxxx ->   xxxxx
xxxxxx     aaxxxx
 <-n->
```

> i(n) = g(n-1)

Thus we can eliminate state `i` from `g`:

> g(n) = f(n) + g(n - 2)

Another observation is that states `g(n)` and `h(n)` are same regarding the count of ways (only mirrored) so

> f(n) = 2 * g(n - 2) + f(n - 2)

Here is code:
```c++
int solve(int n)
{
    std::vector<int> f(n + 1), g(n + 1);
    f[0] = g[0] = 1;
    f[1] = g[1] = 0;

    for (int i = 2; i <= n; i++)
    {
        f[i] = f[i - 2] + 2 * g[i - 2];
        g[i] = g[i - 2] + f[i];
    }

    return f[n];
}
```

The real tricky part are base cases. For state `g(0)` we have 1 way which makes sense, we place one tile filling it. Not sure why for `f(0)` we have one way. For `f(1)` and `g(1)` makes sense there are no way how to fill it in, because can't fill single 3x1 column with 2x1 domino (even if there are two extra spaces for g-case).

## Number of ways n can be written as sum

Number of ways `n` can be written as sum of {1,2,3}

### Solution

1 can be written as:

> 1 =  { 1 }

2 can be written as:

> 2 = { 1 + 1, 2}

3 can be written as:

> 3 = { 1 + 1 + 1, 2 + 1, 1 + 2, 3 }

Now how can we write 4 ?

* we can take all the ways we write 3 and add 1 to it
> 4 = {1 + 1 + 1 `+1`, 2 + 1 `+1`, 1 + 2 `+1`, 3 `+1` }
* we can take all the ways to write 2 and add 2 to it
> 4 = { 1 + 1 `+2`, 2 `+2`}
* we can take all the ways to write 1 and add 3 to it
> 4 =  { 1 `+3` }

Thus the recurrence relation is:

> f(n) = f(n-1) + f(n-2) + f(n-3)

with base cases:

f(1) = 1, f(2) = 2, f(3) = 3

## Binomial coefficient

`c(n,k)` used to denote the number of ways to choose `k` elements out of `n` (also called n choose k)

Also it represents coefficient `x^k` in the expansion of `(1+x)^n`

For example we have 4 elements and choosing 2:  

```
(1 + x)^4 = x^4 + 4x^3 + 6x^2 + 4x + 1
```

Coefficient of `x^2` is `6` which means we have 6 number of ways to choose 2 elements out of 4.

Coefficients also forms pascal's triangle:

```
               1
              1 1
             1 2  1
           1  3  3  1
         1   4  6  4  1
       1   5  10 10  5  1
     1   6  15 20 15  6   1
```

For example on 5th row we can see numbers `{1,4,6,4,1}` which are coefficients of `(1+x)^4` from above.

There are a lot of patterns in Pascal's triangle. 

### Sum of two numbers above gives number below

For example for row numbers `1 3 3 1` we will sum all the consecutive pairs (but we need to imagine 0 on left and right ?). We will get `0+1 1+3 3+3 3+1 1+0 = 1 4 6 4 1`

### Row series

__First row__ are all ones `{1,1,1,1,1,1}`

__Second row__ are counting numbers `{1,2,3,4,5,6}`

__Third row__ are triangular numbers `{1,3,6,10,15}`. If you check the difference between consecutive elements they are `{2,3,4,5}` which are counting numbers.

__Fourth row__ are `{1,4,10,20}`. If you again check the difference it is `{3,6,10}` which seems to be triangular numbers.

### Counting number squared

If you pick counting number, it's square is equal to sum of neighbor to right and right-down. For example

```
   5  10
    15
```

`5^2 = 10 + 15` 

### Sums of rows

Sums of rows are `1 2 4 8 16 32 64` which is `2^n`

### 11th row power

11 raised to the power of row number gives coefficients.

```
11^0 = 1
11^1 = 11
11^2 = 121
11^3 = 1331
11^4 = 14641
11^5 = 161051
11^6 = 1771561
```

5th and 6th power does not match because we have numbers with two digits in triangle. If we write the coefficients from triangle from right like this and sum we get the 11the power (numbers overlap):

```
  1051
 10
15
------
161051
```

### Solution

Solution is simple. If we are picking the `k` elements out of `n` for each element we just decide whether it will be included or not. This will lead to following recursive relation:

```
c(n,k) = c(n-1,k-1) + c(n-1,k)
```

First case if if we have included the element (pick `k-1` from the remaining ones) and second if we skip current element. The base case should be if `n` is same as `k` return 1 (we must pick all the elements).

## Friends Pairing Problem

Given `n` friends, each one can be paired or stay single. Each friend can be paired once. Find out total number of ways in which friends can remain single or be paired up.

### Example

If we have 3 friends `(1,2,3)` possible solutions are:
* 1,2,3 - all remain single
* 12,3
* 1,23
* 2,13

### Recursive Relation

If we have `n` friends we can define recursive relation as follows. We will consider the right-most friend `n`th:

> `f(n)` tells us number of ways in which `n` friends can pair up or remain single

```
f(n) = f(n-1) +
```

`f(n-1)` counts the number of ways if `n`th friend remains single. In that case `n-1` friends can pair up anyway they want.

Now the `n`th friend can pair with `n-2` friend. If that is the case in how many ways the rest can pair ? In `f(n-2)` ways:

```
f(n) = f(n-1) + f(n-2) +
```

But the `n`th friend can decide to pair up with `n-3` friend. In that case the rest can again pair in `f(n-2)` ways:

```
f(n) = f(n-1) + f(n-2) + f(n-2)
```

Overall the `n`th friend can pair with any of `n-1` remaining friends so:

```
f(n) = f(n-1) + (n-1) * f(n-2)
```

## Partition N Into Positive Integers

Count number of ways we can partition number N into positive integers

### Example - order matters

*1* : 
```
1
```

*2* :
``` 
1 + 1

2
```

*3* :
```
1 + 1 + 1
1 + 2

2 + 1

3
```

*4* :
```
1 + 1 + 1 + 1
1 + 1 + 2
1 + 2 + 1
1 + 3

2 + 1 + 1
2 + 2

3 + 1

4
```

### Recursive Relation - order matters

If you take a look at the example, you can find out that we always take previous partition and add `1 +` in front of it. Then we take the partition one more above and add `2 +` in front of it.

So the recursive relation will be, take all partitions above + partitions one more above and `+1` at the end for the number itself:

```
f(n) = f(n-1) + f(n-2) + ... + f(n-n)
```

and base case for `n=0` will be 1.

### Implementation - order matters

__Top-down approach in O(n^2) (no memoization)__

```c++
int solve(int n)
{
    if (n == 0)
        return 1;

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans += solve(n - i);

    return ans;
}
```

__Bottom-up approach in O(n)__

`f(n)` is sum of previous states, for example
```
f(5) = f(4) + f(3) + f(2) + f(1) + 1
```
the `+1` at the end is the number itself , in the example partition `5`.

We will be calculating result from right to left. We will define variable `sum` which will represent the __previous sum__. 

```c++
int solve(int n)
{
    int sum = 0;
    int dp[n + 1];

    for (int i = 1; i <= n; i++)
    {
        dp[i] = sum + 1;
        sum += dp[i];
    }

    return dp[n];
}
```

Here is how values will be set for different `i`s:
```
|i           | 1 | 2 | 3 | 4  | 5  |
|------------|---|---|---|----|----|
|sum - begin | 0 | 1 | 3 | 7  | 15 |
|dp          | 1 | 2 | 4 | 8  | 16 |
|sum - end   | 1 | 3 | 7 | 15 | 31 |
```

We can see that `dp` is just power of two :)

__Mathematical formula in O(1)__

```c++
return pow(2, n - 1)
```

### Example - order doesn't matter

From the previous example for number `4` we have following partionions
```
1 + 1 + 1 + 1
1 + 1 + 2
remove 1 + 2 + 1
1 + 3
remove 2 + 1 + 1
2 + 2
remove 3 + 1
4
```

We have removed all the partitions that are not in `increasing` order (we may have also choose decreasing or something else).

### Recursive Relation - order doesn't matter

In a recursion we will remember the minimum number we can use for partitioning.

```
dp(min, n) -> number of ways to partition n such that minimum element is min
```

```
dp(min, n) = for i=min to n : dp(i, n - i)
```

### Implementation - order doesn't matter

```c++
int solve(int min, int n)
{
    if (n == 0)
        return 1;

    int ans = 0;
    for (int i = min; i <= n; i++)
        ans += solve(i, n - i);

    return ans;
}

solve(1, i);
```

We will start with minimum of `1` so first we will recurse like this (`i` is always `1` in all for loops) finding the partition of all `1`s

```
1+1+1+1+1
```

Then we will in the last for loop increment `min` to `2` finding the partition

```
1+1+1+1+2
```

and so on. The trick is that the partition will be always in increasing order.

This implementation is in O(n^3)

Resulting series is not computable in O(1) (according to `oeis`)

### Recursive Relation 2 - order doesn't matter

In a recursion we will remember the minimum number we can use for partitioning. So the state is the same but `min` will in this case represent the least min that can be used (so we can use min+1, min+2, ...)

```
dp(min, n) -> number of ways to partition n such that minimum element is at least min
```

```
dp(min, n) = dp(min, n-min) + dp(min + 1, n)
```

There are two recursion cases:
* `dp(min, n-min)` - in this case we will use `min` to partition n
* `dp(min + 1, n)` - in this case we will discard `min` and move on using larger `min` with the same `n`

### Implementation 2 - order doesn't matter

Top-down in O(n^2)
```c++
int solve(int min, int n)
{
        if (n == 0) return 1;
        if (min > n) return 0;
        if (min == n) return 1;

    int ans = solve(min, n - min) + solve(min + 1, n);

    return ans;
}
```

Bottom-up in O(n^2)

|   | | 0 | 1 | 2 | 3 | 4 | 5 | 6  |
|---|-|---|---|---|---|---|---|----|
| 0 | | 1 |   |   |   |   |   |    |
| 1 | | 1 | 1 | 2 | 3 | 5 | 7 | 11 |
| 2 | | 1 | 0 | 1 | 1 | 2 | 2 | 4  |
| 3 | | 1 | 0 | 0 | 1 | 1 | 1 | 2  |
| 4 | | 1 | 0 | 0 | 0 | 1 | 1 | 1  |
| 5 | | 1 | 0 | 0 | 0 | 0 | 1 | 1  |
| 6 | | 1 | 0 | 0 | 0 | 0 | 0 | 1  |

the relation is `dp(i,j) = dp(i, j-i) + dp(i+1,j)`

* row is `i`
* col is `j`

That means we need value to the left and one down. For example cell `[2,4]`:

|   | | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|---|-|---|---|---|---|---|---|---|
| 0 | |   |   |   |   |   |   |   |
| 1 | |   |   |   |   |   |   |   |
| 2 | |   |   | x |   | O |   |   |
| 3 | |   |   |   |   | x |   |   |
| 4 | |   |   |   |   |   |   |   |
| 5 | |   |   |   |   |   |   |   |
| 6 | |   |   |   |   |   |   |   |

So we need to fill in the table from bottom up and from left to right.

The base cases are like this:

```c++
    if (j == 0) return 1;
    if (i > j) return 0;
    if (i == j) return 1;
```

So we will prefill the table

|   | | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
|---|-|---|---|---|---|---|---|---|
| 0 | | 1 |   |   |   |   |   |   |
| 1 | | 1 |   |   |   |   |   |   |
| 2 | | 1 |   |   |   |   |   |   |
| 3 | | 1 |   |   |   |   |   |   |
| 4 | | 1 |   |   |   |   |   |   |
| 5 | | 1 |   |   |   |   |   |   |
| 6 | | 1 | 0 | 0 | 0 | 0 | 0 | 1 |

From now on we can start filling in. One optimization is, we can use only single row and to each cell add `dp(i, j-1)` (because the term `dp(i+1,j)` will already be there).

```c++
int solve3(int n)
{
    std::vector<int> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
            dp[j] += dp[j - i];
    }

    return dp[n];
}
```

TODO this is slightly different implementation than explained. Tried to implement it differently but doesn't work.

# Subsequences

## Longest Increasing Subsequence

Find the longest increasing subsequence in a sequence of numbers. Subsequence does not have to be continuous.

### Example

```
7 49 23 8 30 22 44 28 23 9 40 15
```

There are multiple subsequences of length 5. One of them is:

```
7 49 23 8 30 22 44 28 23 9 40 15
x       x    x        x    x
```

### Solution

```
f(n) - longest increasing subsequence including only first n numbers
```

We will maintain dp state which will contain longest subsequence which ends on that number

For example above we will create dp:

```
7 49 23 8 30 22 44 28 23 9 40 15
0 0  0  0 0  0  0  0  0  0 0  0
```

We will start filling in dp from left to right.

Sequence that ends on `7` has only `7` so the longest is one:

```
7 49 23 8 30 22 44 28 23 9 40 15
1 0  0  0 0  0  0  0  0  0 0  0
```

Sequence that ends on `49` can contain also `7` so the length is 2:

```
7 49 23 8 30 22 44 28 23 9 40 15
1 2  0  0 0  0  0  0  0  0 0  0
```

Sequence that ends on `23` can contain `7` but can't contain `49` so the length is again 2:

```
7 49 23 8 30 22 44 28 23 9 40 15
1 2  2  0 0  0  0  0  0  0 0  0
```

Sequence that ends on `8` can contain only `7`:

```
7 49 23 8 30 22 44 28 23 9 40 15
1 2  2  2 0  0  0  0  0  0 0  0
```

Sequence that ends on `30` can contain `23` so the length is 3:

```
7 49 23 8 30 22 44 28 23 9 40 15
1 2  2  2 3  0  0  0  0  0 0  0
```

And so on:

```
7 49 23 8 30 22 44 28 23 9 40 15
1 2  2  2 3  3  4  4  4  3 5  4
```

```c++
int solve(const std::vector<int>& data)
{
    std::vector<int> dp(data.size(), 0);

    for (int i = 0; i < data.size(); i++)
    {
        int ans = 1;
        for (int j = 0; j < i; j++)
        {
            if (data[j] <= data[i])
                ans = std::max(ans, dp[j] + 1);
        }
        dp[i] = ans;
    }

    return std::max_element(std::begin(dp), std::end(dp));
}
```

## Good Sequences

> [CodeForces](https://codeforces.com/problemset/problem/264/B)

```
Squirrel Liss is interested in sequences. She also has preferences of integers. She thinks n integers a1, a2, ..., an are good.

Now she is interested in good sequences. A sequence x1, x2, ..., xk is called good if it satisfies the following three conditions:

    The sequence is strictly increasing, i.e. xi < xi + 1 for each i (1 ≤ i ≤ k - 1).
    No two adjacent elements are coprime, i.e. gcd(xi, xi + 1) > 1 for each i (1 ≤ i ≤ k - 1) (where gcd(p, q) denotes the greatest common divisor of the integers p and q).
    All elements of the sequence are good integers. 

Find the length of the longest good sequence.
```

### Example

```
2 3 4 6 9
```

From the example above, we can create longest good sequence with size 4: `2 4 6 9` because it's increasing and all two adjacent integers has gcd > 1 (`gcd(2,4) == 2`, `gcd(4,6) = 2`, `gcd(6,9) = 3`)

### Solution

Naive solution in `O(n^2)`

```c++
int32_t solve(std::vector<int32_t>& array)
{
    std::vector<int32_t> dp(array.size(), 1);
    for (int32_t i = 1; i < dp.size(); i++)
    {
        for (int32_t j = i - 1; j >= 0; j--)
        {
            if (gcd(array[i], array[j]) > 1)
                dp[i] = std::max(dp[i], dp[j] + 1);
        }
    }

    return *std::max_element(std::begin(dp), std::end(dp));
}
```

A note, gcd can be get like this:
```c++
int32_t gcd(int32_t a, int32_t b)
{
    if (a == b)
        return a;
    if (a > b)
        return gcd(a - b, b);
    else
        return gcd(a, b - a);
}
```

---

But there is also better solution using prime numbers as follows:

We will allocate `dp` array for longest length ending in that number but also the `prime` array.

`prime` array will be an array which will represent longest subsequence when number has particular prime in it's prime factors

Here is an example with prime factors written below:
```
2 3 4 6 9
2 3 2 2 3
      3
```

Now we will maintain `dp` and `prime` arrays.

```
    2 3 4 6 9
    2 3 2 2 3
          3
dp: 0 0 0 0 0
       2 3
prime: 0 0
```

When considering the first number `2` at index 0. We will check what's the longest sequence which can any number with prime `2` provide? It's 0 so we will pick 0 + 1 to `dp` and update also prime array:

```
    2 3 4 6 9
    2 3 2 2 3
          3
dp: 1 0 0 0 0
       2 3
prime: 1 0
```

Same way we will continue with `3`:

```
    2 3 4 6 9
    2 3 2 2 3
          3
dp: 1 1 0 0 0
       2 3
prime: 1 1
```

Now number `4` has prime `2`, we will check the `prime` array and we can see that longest sequence for any number with prime `2` is 1. So we will update here with 1 + 1 both `dp` and `prime`

```
    2 3 4 6 9
    2 3 2 2 3
          3
dp: 1 1 2 0 0
       2 3
prime: 2 1
```

Now the tricky part. Number `6` has two factors `2` and `3`. We will check the `prime` array for the longest sequences we can get. It's `2` and `1` so we will pick 2 + 1 here.
> But the thing is even though we have used prime `2` we should update also prime `3`, because any later number with prime `3` can use this `6` in it's longest good sequence.

```
    2 3 4 6 9
    2 3 2 2 3
          3
dp: 1 1 2 3 0
       2 3
prime: 3 3
```

And `9` will use previous number `6` using the prime `3`

```
    2 3 4 6 9
    2 3 2 2 3
          3
dp: 1 1 2 3 4
       2 3
prime: 3 4
```

```c++
int32_t solve(std::vector<int32_t>& array)
{
    std::vector<int32_t> dp_prime(array.size(), 0);

    for (int32_t i = 0; i < array.size(); i++)
    {
        auto primes = prime_factors(array[i]);

        // iterate over prime numbers of number in array and find the best ending in dp_prime
        int32_t best = 0;
        for (auto x : primes)
            best = std::max(best, dp_prime[x]);

        // update the dp_prime with best value for all primes
        for (auto x : primes)
            dp_prime[x] = best + 1;
    }

    return *std::max_element(std::begin(dp_prime), std::end(dp_prime));
}
```

We don't use the `dp` array mentioned above, it's not needed.

A note, here is how to get prime factors in `O(sqrt(n))`

```c++
std::vector<int32_t> prime_factors(int32_t n)
{
    std::vector<int32_t> result;

    for (int32_t i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            result.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }

    if (n > 1)
        result.push_back(n);

    return result;
}
```

## Consecutive Subsequence

> [CodeForces](https://codeforces.com/problemset/problem/977/F)

```
You are given an integer array of length n.

You have to choose some subsequence of this array of maximum length such that this subsequence forms a increasing sequence of consecutive integers. In other words the required sequence should be equal to [x,x+1,…,x+k−1]
for some value x and length k.

Print the length of the result and indices that forms the resulting subsequence.
```

### Example

```
7
3 3 4 7 5 6 8
```

Result:
```
4
2 3 5 6 
```

We can pick subsequence with length `4` with indices `2,3,5,6` which forms subsequence `3,4,5,6` (one-based indexing).

### Solution

There are two parts. First the dp to get the lenght and dp array and then printing the actual indices. When you think about it, dp is very simple. We just iterate from left to right and for each number checking the number one smaller and using it to dp like this:

```
f(x) = f(x-1) + 1
```

```c++
using map = std::map<int32_t, int32_t>;

void solve(std::vector<int32_t>& array)
{
    map dp;
    // indexing to array for non-existing element will return default initialized int to 0
    for (auto n : array)
        dp[n] = dp[n - 1] + 1;
```

(we use map here because the numbers in array can be up to 1e9)

The index part can be as follows:
```c++
    // find the number with highest dp value (length)
    int64_t max_n = 0, max_val = 0;
    for (const auto& [n, val] : dp)
    {
        if (val > max_val)
        {
            max_val = val;
            max_n = n;
        }
    }

    std::cout << max_val << "\n";

    std::vector<int64_t> subsequence_indices;
    for (int i = array.size() - 1; i >= 0; --i)
    {
        if (array[i] == max_n)
        {
            subsequence_indices.push_back(i + 1);
            --max_n;
        }
    }

    for (auto it = std::rbegin(subsequence_indices); it != std::rend(subsequence_indices); it++)
        std::cout << *it << " ";
```

# Multi-Dimensional DP

Multi-Dimensional DP means that state is made of multiple independent variables. For example if state is made of 3 variables:

`f(x, y, z)` - this is 3D DP

but all variables should be independent, i.e. there is no relation like this `x = f(y, z)`

# Digit Dynamic Programming

Problems in this section consists of printing all numbers within some range which satisfies some properties. We should be able to print all numbers __using recursion__ .

## Print recursively numbers from 0 to 2437

__2437__

We need to print 4 digits. On first place we can put numbers from 0 to 2 including:
```
 _ _ _ _
0-2
```

The second place depends on what we have chosen for the first place. For example if we have chosen for the first place number `1` second place can be any number from `0-9`:

```
 1 _ _ _
  0-9
```

But if on the first place is last number `2` we can choose for the second place only numbers from range `0-4` (because choosing anything higher than `4` will mean we will end up with number higher than `2437`):

```
 2 _ _ _
  0-4
```

This condition holds for all numbers, for the third place we are in the same situation like this:

```
 2 4 _ _   or 2 0 _ _
    0-3          0-9
```

From this we can form recursive algorithm that will print all the numbers:

```c++
void fun(const string& max_number, string answer, int index, bool last)
{
    if (index == max_number.size())
    {
        std::cout << answer << '\n';
        return;
    }

    int till = last ? max_number[index] - '0' : 9;

    for (int i = 0; i <= till; i++)
        fun(max_number, answer + to_string(i), index + 1, last && i == till);
}
```

In the algorithm `last` represents whether this is the last branch of previous for loop. One important thing, this function should be called initially with `last` set to `true`. The left most branch must be constrained with `till`.

## Sum of Digits

Calculate the sum of digits of numbers from `a` to `b`.

### Example

Sum of digits of numbers from `1` to `10`. In this range we have following numbers `1,2,3,4,5,6,7,8,9,10` and the sum of digits is `1+2+3+4+5+6+7+8+9+1+0` = `46`.

```c++
int dp(const std::string& max_number, int index, bool last, int sum)
{
    if (index == max_number.size())
        return 1;

    int till = last ? max_number[index] - '0' : 9;
    int ans = 0;

    for (int i = 0; i <= till; i++)
        ans += dp(max_number, index + 1, last && i == till, sum + i);
    
    return ans;
}
```

## Investigation

Calculate number of digits `d` in some range from `a` to `b` which satisfies following conditions
* `d` is divisible by `k`
* sum of digits of `d` is divisible by `k`

### Example

3702 is divisible by 3
(3+7+0+2) = 12 is divisible by 3

### Solution

We will be using recursion to iterate over all numbers. If we have function `f` which counts the numbers that satisfies conditions the result will be obtained by

```
answer = f(b) - f(a-1)
```

#### Divisibility check in recursion

In order to check whether number `d` is divisible by `k` we utilize fact:

> mod is distributed across addition and multiplication:

```
(a + b*c) % m = a % m + (b*c) % m
```

If we have some number for example `3245`, it can be written as `((3*10 + 2)*10 + 4)*10 + 5` then

```
3245 % m = [[([([3*10]%m + 2)*10]%m + 4)*10]%m + 5]%m
```

In other words, we can take `mod` operation in the process of the forming the number in recursion and come up with the result to `3245 % m`

```c++
int solve(const std::string& number, int mod, int index, bool last, int num_mod, int sum_digit_mod)
{
    if (index == number.size())
    {
        if (num_mod == 0 && sum_digit_mod == 0)
            return 1; // we have found number that satisfies both properties
        return 0;
    }

    int till = last ? number[index] - '0' : 9;
    int ans = 0;

    for (int i = 0; i <= till; i++)
    {
        ans += solve(number,
                     index + 1,
                     last && i == till,
                     (num_mod*10 + i) % mod, // this is computation of mod of whole number
                     (sum_digit_mod + i) % mod); // this is computation of mod of sum of digits
    }

    return ans;
}
```

Solution above is only recursion without memoization. Now, how many different states can `solve` have ? First two parameters `number` and `mod` must be ignored as those does not change.
* `index` is index to the number which according to description is up to 2^31 so index can go up to `10`
* `last` has two different values
* `num_mod` is only up to `mod` number
* `sum_digit_mod` same as `num_mod` up to `mod`

We can easily memoize the states of this function:

```c++
int memo[10][2][mod][mod]
```

and can solve numbers up to 10 digits.

### Trick

So the above memoization is not that great. If mod is 10^4 we have 10*2*10^4*10^4 = 2*10^9 which is two gigabytes. But let's think about it. 

`sum_digit_mod` is modulo of the sum of the digits of the numbers. If we have numbers up to the 2^31 number can have up to 10 digits. If we have all the nines there:

```
9+9+9+9+9+9+9+9+9=9*10=90
```

So that means the sum can go only up to 90! (this is not factorial (: ) And modding 90 with any greater number will still result with 90. So the last state can be reduced to 90. Another observation is

> if `mod` is greater than 90 can ever `sum_digit_mod` be 0 ?

We will be increasing `sum_digit_mod` up to maximum value of 90 and modding it with for example 100. But the number mod greater number won't ever get chance to wrap around to 0. This means that calling `solve` if `mod` is greater than 90 (or maximum sum of digits) is waste of time. This means that if `solve` is called only with `mod` less or equal to 90 we will end up with following space requirement for memoization:

```c++
int memo[10][2][90][90]
```

## Magic numbers

> [CodeForces](https://codeforces.com/problemset/problem/628/D)

```
Consider the decimal presentation of an integer. Let's call a number d-magic if digit d appears in decimal presentation of the number on even positions and nowhere else.

For example, the numbers 1727374, 17, 1 are 7-magic but 77, 7, 123, 34, 71 are not 7-magic. On the other hand the number 7 is 0-magic, 123 is 2-magic, 34 is 4-magic and 71 is 1-magic.

Find the number of d-magic numbers in the segment [a, b] that are multiple of m. Because the answer can be very huge you should only find its value modulo 10^9 + 7 (so you should find the remainder after dividing by 10^9 + 7).
```

```c++
int m, d;
int MOD = 1e9 + 7;

int solve_rec(const std::string& number, int index, bool last, int num_mod)
{
    if (index == number.size())
    {
        if (num_mod == 0)
            std::cout << test << "\n";

        return num_mod == 0;
    }

    int till = last ? number[index] - '0' : 9;
    uint32_t ans = 0;

    if ((index + 1) % 2 == 0 && d <= till) // zero-based indexing
    {
        ans += solve_rec(number, index + 1, last && d == till, (num_mod * 10 + d) % m);
        ans %= MOD;
    }
    else
    {
        for (int i = 0; i <= till; i++)
        {
            if (i == d)
                continue;

            ans += solve_rec(number, index + 1, last && i == till, (num_mod * 10 + i) % m);
            ans %= MOD;
        }
    }

    return ans;
}

int solve(const std::string& number)
{
    return solve_rec(number, 0, true, 0);
}

int main()
{
    std::string a, b;
    std::cin >> m >> d >> a >> b;

    // What we need is f(b) - f(a-1). In order to get a-1 we do following:
    int i = a.size() - 1;
    while (i >= 0 && a[i] == '0') {
        a[i] = '9';
        i--;
    }
    a[i] = a[i] - 1;

    // Here we need to add MOD because of subtraction. Why?
    std::cout << (solve(b) - solve(a) + MOD) % MOD;

    return 0;
}
```

# Dynamic Programming on Trees

Tree is a datastructure with nodes and edges.

> If tree has `n` nodes there is exactly `n-1` edges.
> Tree is connected.
> Degree of node is number of edges of that particular node.

There is also another structure DAG (Directed Acyclic Graph) which is similar to tree but it does not adhere to property of `n-1` edges.

Root of the tree usually doesn't matter (if not stated in the description). For example following are the same trees:

```
     1          2
   / | \       / \
  2  3  4     5   1
  |  |  |        / \
  5  6  7       3   4
                |   |
                6   7
```

Also naming of the vertices doesn't matter. We may the root of second tree above call 1 but the structure doesn't changes and that's what matter.

If we call `dp(n)` we will call it on subtree from the node `n`. For example above the subtree of node `2` is either only node `5` or all other the nodes (second tree). So the subtree depends on the root node. But the overall solution (i.e. `dp(root)`) should not depend on what root we choose.

## Vertex Cover

You are given unweighted, undirected tree. Write a program to find a vertex set of *minimum* size in this tree such that each edge has at least one of it's end-points in that set.

### Example

```
    1
   / \
  2   3
```

In the example above the answer is { 1 }. Other answers {2,3} or {1,3} has size of two.

### Greedy approach

One may be tempted to use greedy approach here. That is:

Repeat until no edges:
* pick the vertex with highest degree
* eliminate covered edges
* recompute degrees

Here is counter example for which this approach will not work:

```
     1
   / | \
  2  3  4
  |  |  |
  5  6  7
```

Algorithm will pick 1 as it is only node with degree 3. After that all nodes will have degree of one so it doesn't matter which but it must pick three another so the resulting set will be for example {1,5,6,7} of size 4. But the optimal solution is {2,3,4}.

### DP approach

We will formulate recurrence relation as follows:

> dp(n, 0) - number of nodes in vertex cover if current node *is not* included
> dp(n, 1) - number of nodes in vertex cover if current node *is* included

```
dp(n, 0) = sum( dp(x, 1) )
dp(n, 1) = 1 + sum( min( dp(x, 0), dp(x, 1) ) )
```

where `x` are children of node `n`

This means:
* if we don't include the current node (`dp(n, 0)`) we must include nodes of children (otherwise edges between current node and children won't be satisfied)
* if we include the current node (`dp(n, 1)`) we pick the best out of including/not-including children. You may be tempted that in this case we should always not include the children, but we don't know and don't care at this point about the structure of the child. TODO example where it is optimal to pick both parent and child.

```c++
const int N = 1e5 + 1;

vector<int> adjacency_lists[N];
int memo[N][2];

int dp(int node, bool take, int parent)
{
    if (memo[node][take] != -1)
        return memo[node][take];

    int ans = take; // this will initialize ans with either 0 or 1
    for (auto child : adjacency_lists[node])
    {
        if (child == parent)
            continue;
        if (take)
            ans += min(dp(x, false, node), dp(x, true, node));
        else
            ans += dp(x, true, node);
    }
    return memo[node][take] = ans;
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n - 1; i++)
    {
        int x, y;
        cin >> x >> y;
        adjacency_lists[x].push_back(y);
        adjacency_lists[y].push_back(x);
    }

    memset(memo, -1, sizeof(memo));
    cout << min(dp(1, false, -1), dp(1, true, -1));

    return 0;
}
```

### DFS approach

In the following code we will perform dfs on the tree, filling in `dp` array on the way back, result will be `min(dp[root][false], dp[root][true])`

```c++
void dfs(int node, int parent)
{
    dp[node][false] = 0;
    dp[node][true] = 1;

    for (auto child : adjacency_lists[node])
    {
        if (child == parent)
            continue;

        dfs(child, node);
        // coming back from dfs, dp[x] wil be filled
        dp[node][false] += dp[child][true];
        dp[node][true] += min(dp[child][false], dp[child][true]);
    }
}
```

### BFS approach

```c++
    queue<int> Q;
    int root = -1;

    // start with the leaf nodes and move upwards to parents, this way we will have final values in dp
    for (int i = 1; i <= n; i++)
    {
       if (adjacency_lists[i].size() == 1)
            Q.push(i);
    }

    while (!Q.empty())
    {
        int node = Q.front();
        Q.pop();

        visited[node] = true;
        root = node;

        dp[node][false] = 0;
        dp[node][true] = 1;

        for (auto child : adjacency_lists[node])
        {
            if (visited[child])
            {
                // child node
                dp[node][false] += dp[child][true];
                dp[node][true] += min(dp[child][false], dp[child][true]);
            }
            else
            {
                // parent node
                Q.push(child);
            }
        }
    }
    // the node which is visited in the end
    cout << min(dp[root][false], dp[root][true]);
```

## Tree diameter

`Tree diameter` is length of the longest path between any two nodes. Length of the path is given by number of edges that forms the path. Find tree diameter.

### Greedy approach

* perform DFS from any node and find the node `x` which is farthest (we need to traverse most edges to go from root to `x`)
* perform DFS from node `x` and find the node `y` which is farthest

Path between `x` and `y` is diameter of tree

There is the notion of `farthest` node. If we form a tree by picking a root node, even if not specified in description, we can talk about farthest node from some node.

### Recursive approach

We will pick a root node and for each node find a distance to farthest node.

Then for each node `n` we have two possibilities:
* either longest path goes through the node `n`
* or longest path does not go through node `n` and is contained within a subtree of node `n`

Here we are considering the longest path that we can obtain by the nodes only within `n` and it's subtree. __This is actually recursive approach, forming longest path recursively by adding node by node__.

To handle both cases we will do following:
* get the longest path that goes through current node by : `(distance to farthest node + 1) + (distance to second to farthest node + 1)` (here is plus one because we add an edge when connecting the subtree to current node)
* or use the longest distance from previous computations

Here is DFS that will fill in table `g` which will contain the `farthest` nodes
```c++
void dfs(int cur, int par)
{
    for (auto x : gr[cur])
    {
        if (x != par)
        {
            dfs(x, cur);
            g[cur] = max(g[x] + 1, g[cur]);
        }
    }
}
```

And here is the rest. We will compute the table `f`. The root node in `f` will contain the final result. 
```c++
void dfs(int cur, int par)
{
    int max_1 = 0, max_2 = 0;

    for (auto x : gr[cur])
    {
        if (x != par)
        {
            dfs(x, cur);

            // fill in the longest path within subtrees of current node (path does not cross current node)
            f[cur] = max(f[x], f[cur]);

            // max 2 values of g[x]
            if (g[x] + 1 > max_1)
            {
                max_2 = max_1;
                max_1 = g[x] + 1;
            }
            else if (g[x] + 1 > max_2)
            {
                max_2 = g[x] + 1;
            }
        }
    }

    // in the end pick either path that goes through current node or is contained within children
    f[cur] = max(f[cur], max_1 + max_2);
}
```

The both steps can be done in single DFS.

## Tree diameter I

You are given a tree consisting of n nodes. Your task is to determine for each node the maximum distance (number of edges) to another node.

### Example

```
    1
   / \
  2   3
     / \
    4   5

Result:
node: 1 2 3 4 5
dist: 2 3 2 3 3
```

### Solution

There is one problem. If we are computing max distance for example for node `3` we need to consider also it's parent distances. Here the max distance within subtree of `3` is 1 (to either `4` or `5`) then there is one edge to parent and there is max distance of 1 within subtrees of parent `1` (to `2`) excluding the `3` node.

Let's add new variable to recursion `dis_par` which will represent max distance obtained from parent. It can be computed by taking `dis_par` we have so far in recursion and max it with distances from another subtrees (expect the child we plan to recurse on). This will form `new_dis_par` used in recursion.

```c++
// The `g` array is initialized to 0 initially. This function below will compute for each node distance to farthest node.
void dfs_g(int cur, int par)
{
    for (auto x : gr[cur])
    {
        if (x != par)
        {
            dfs_g(x, cur);
            g[cur] = max(g[cur], g[x] + 1);
        }
    }
}

void dfs_f(int cur, int par, int dis_par)
{
    for (auto x : gr[cur])
    {
        if (x != par)
        {
            // here we are creating new_dis_par by either taking dis_par from parent or any children expect current child x (and ofc parent), we will then add +1 because of edge to child
            int new_dis_par = dis_par;
            for (auto y : gr[cur])
            {
                if (y != par && y != x)
                    new_dis_par = max(g[y], new_dis_par);
            }

            dfs_f(x, cur, new_dis_par + 1);

            // so here the result is considering the child nodes
            f[cur] = max(f[cur], g[x] + 1);
        }
    }

    // for any node in the supertree
    // supertree = compliment of subtree
    f[cur] = max(f[cur], dis_par + 1);
}
```

There are two nested for loops so the complexity is O(N^2) in worst case, but can be easily reduced to O(N) by finding two max values single time instead of iterating over all childs each time.

```c++
void dfs_f(int cur, int par, int dis_par)
{
    int max_1 = -1, max_2 = -1;

    for (auto x : gr[cur])
    {
        if (x != par)
        {
            if (g[x] > max_1) max_2 = max_1, max_1 = g[x];
            else if (g[x] > max_2) max_2 = g[x];
        }
    }

    for (auto x : gr[cur])
    {
        if (x != par)
        {
            int new_dis_par = dis_par;

            if (g[x] == max_1)
                new_dis_par = max(new_dis_par, max_2);
            else
                new_dis_par = max(new_dis_par, max_1);
```

Here we will use either `max_2` if what we have is `max_1` otherwise we use `max_1` 

## Tree diameter II

You are given a tree consisting of n nodes. Your task is to determine for each node the sum of the distances to all other nodes.

### Example

```
    1
   / \
  2   3
     / \
    4   5
```

Here for example for node `1` result is 6:

```
1-2 = 1
1-3 = 1
1-4 = 2
1-5 = 2

1 + 1 + 2 + 2 = 6
```

### Solution

As an example above in order to compute sum of distances from parent node to all other nodes we need to first know number of nodes in each subtree:

```c++
void dfs_h(int cur, int par)
{
    for (auto x : gr[cur])
    {
        if (x != par)
            h[cur] += h[x];
    }
    h[cur] += 1;
}
```

Then we can compute the sum of distances from current node to it's subtree like this:

```c++
void dfs_g(int cur, int par)
{
    for (auto x : gr[cur])
    {
        if (x != par)
        {
            dfs_g(x, cur);
            g[cur] += g[x] + h[x];
        }
    }
}
```

For each node we will iterate over all children and add to overall sum the previously computed value of that child and number of children of that child.

Now comes re-routing. We have distances from within subtree and now we need to add distances from parent.

```c++
void dfs_f(int cur, int par, int sum_par)
{
    // this variable represents number of nodes in tree except the subtree at cur (n is total number of nodes)
    int num_par_nodes = n - h[cur];

    for (auto x : gr[cur])
    {
        if (x == par)
            continue;

        // here we need to compute new_sum_par for child
        int new_sum_par = sum_par + num_par_nodes;
        int current_child_values = g[x] + h[x];
        new_sum_par += (g[cur] - current_child_values);

        dfs_f(x, cur, new_sum_par);

        // here we add distances contained within the child
        f[cur] += (g[x] + h[x]);
    }

    // here we add to the result sum of distances contained outside of subtree of the cur node
    f[cur] += sum_par + num_par_nodes;
}
```
