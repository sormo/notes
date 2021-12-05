# Combinatorial Games

Two-person games with perfect information, no chance moves and win-or-lose outcome. Alice and Bob are playing optimally. Finite set of position of game.

* __Impartial Games__ - set of moves is same (for both players) for given position of game.
* __Partisan Games__ - set of moves (for each player) is different for given position of game. (for example chess)

__Terminal position__ - position of game when no player is not able to make a move.

* __Normal Rule__ - the last player to make a move wins (player who can't make a move lose).
* __Misere Rule__ - the last player to make a move lose.

## Take Away Game

Pile of stones. Each time one player can take 1, 2 or 3 stones. Normal rule - player who can't make a move lose.

Backward Induction:
```
0 1 2 3 4 5 6 7 8 9 10 11 12  ...
L W W W L W W W L W W  W  L   ...
```
From left-to-right, 0 stones is lose. 1,2,3, stones is win because player can take all stones from pile. 4 is lose because game can get only to win position after making move. And so on.

win `n % 4 == 0`

---

Initially there is number `n` on chalk board. Each player has move consisting of:
* choosing any `x` with `0 < x < n` and `n % x == 0`
* replace number `n` on chalkboard with `n - x`

Normal rule, player who can't make a move lose.

Backward Induction:
```
1 2 3 4 5 6 7 8 9 10 11 12  ...
L W L W L W L W L W  L  W
```
It can be seen that 1 is loosing position. From 1 we can get to loosing position so it's winning position. From 3 we can subtract only 1 so we can get only to winning position so it's loosing position.

win `n % 2 == 0`

---

Pile of stones, only now can be taken 1,2,3,4,5 stones:
```
0 1 2 3 4 5 6 7 8 9 10 11 12  ...
L W W W W W L W W W W  W  L
```
win `n % 6 == 0` 

---

Pile of stones, only now can be take 2,4 stones:
```
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14  ...
L L W W W W L L W W W  W  L  L  W
```
win `n % 6 == 0 || n % 6 == 1`

---

Pile of stones. 1,2,3 can be taken, misere rule.
```
0 1 2 3 4 5 6 7 8 9 10 11 12  ...
W L W W W L W W W L W  W  W
```

## Generic Algorithm

When game has normal rule, so player in `Terminal position` loses:
1. Mark all terminal position `L`
2. Mark all positions which can reach `L` position as `W` position
3. Mark all positions from which we can move only to `W` positions as `L` position
4. If no new positions marked, break, otherwise move to 2.

## Empty and Divide

There are two boxes with `m` and `n` chips respectively (`m > 0` and `n > 0`). Two players alternate turns. Turn consists of emptying one box and dividing the content of the other one between the two boxes with at leas one chip in each box. There is single terminal position `(1,1)`

```
(1,1) - L
(1,2) - W (2,2) - W
(1,3) - L (2,3) - W (3,3) - L 
(1,4) - W (2,4) - W (3,4) - W
(1,5) - L (2,5) - W (3,5) - L
```
win `m % 2 == 0 || n % 2 == 0`


# Game of Nim

In a game of Nim there are three piles of chips. Two players alternate turns. In each turn player must remove some number of chips from single pile. If player is not able to make turn he loses.

Terminal position: (0,0,0)

## One Pile Positions

(0,0,x) - these positions are always winning positions, because player can remove x chips leaving terminal position for second player

## Two Pile Positions

(0,1,1) - this is loosing position (leads to one pile position)

(0,x,x) - if number of chips is same this is loosing position because if player removes x chips this leads to one pile position and if player removes some number y chips this leads to (0,x-y,x) and opponent can even it by removing y from other pile which leads to (0,x-y,x-y). This leads to either (0,1,1) or one pile position.

## Three Pile Positions

(y,x,x) - this is winning position because can be converted to (0,x,x) which is loosing position.

If all three numbers are different:
```
(1,2,3) -> (0,2,3), (1,1,3), (1,2,2)
                    (1,0,3), (1,2,1)
                             (1,2,0)
```
It can be verified that all the positions above are winning positions so

(1,2,3) - loosing position

## Nim Sum

Nim sum is sum of piles in special way - addition without carry, sum of bits modulo 2.

For example:
```
5 + 3 = 101
         11
        ---
        101
```
The cary does not cary over, this is identical to __XOR__ operation. In other words, each pair of ones at some (bit) position will cancel out.

__Theorem__:
> In game of nim if nim-sum is 0, this is loosing position.

For example, we have nim sum (1,3,5,7). Nim sum is `1 ^ 3 ^ 5 ^ 7 = 0`. This means (1,3,5,7) is loosing position.

__Lemma 1__:
> If nim-sum is 0, player must change it to non-0 in it's turn.

__Lemma 2__:
> It is always possible to make nim-sum 0 in single turn if it was not zero at the beginning of turn.

From this is clear that position with nim-sum equal 0 is loosing position because, loosing player must change position to non-zero sum and the winning player will change it again to zero sum.

The key is canceling of the pairs of bits.

## Nim Games

__Nim Game II__

There are `n` heaps of sticks. Player can each turn remove 1, 2 or 3 sticks from single heap.

---

This can be converted to nim game by converting heap sizes to modulo 4.

__Nimble__

Game board consists of line of squares labeled from 0 to n. A finite number of coins is placed on the squares with possibly more then one coin on single square. A move consists of taking one coin and moving it to any square on the left. Game ends when all coins are on square 0.

---

This can be simply converted to nim by considering squares as piles. For example:
```
square:       0  1  2  3  4  5  6  7  8
num of coins: 2  3  0  1  0  0  2  1  0
```
Will be converted to nim game with following piles:
```
0, 0, 1, 1, 1, 3, 6, 6, 7
```
Moving coin from 3rd square to 2nd square will mean decrementing pile with with 3 to 2.

__Turning Turtles__

A horizontal line of coins is laid out randomly with some coins showing heads and some tails. A move consists of flipping coin from head to tail and in addition, if desired, flipping over one of the coins to the left (from heads to tails or tails to heads). Game ends when all coins are flipped to head.

---

There are three possible moves:
1. H->T
2. H->T, T->H
3. H->T, H->T

Example:
```
1  2  3  4  5  6  7  8  9 10 11 12 13
T  H  T  T  H  T  T  T  H  H  T  H  T
```
Let's create piles for nim by setting size of pile to coin index if coin is on Head
```
1  2  3  4  5  6  7  8  9 10 11 12 13
0  2  0  0  5  0  0  0  9 10  0 12  0
```
1. H->T
`H->T` is valid move within nim, it means setting whole pile of coin to zero.

2. H->T, T->H

`H->T, T->H` means that we will take some pile and make it zero and then we will some other pile and make it non-zero (coin index). Here is crucial that the `T->H` coin will have lower index (because it's to the left), so this operation can be seen as single move of reducing single pile.

From example above we will flip coin 9 from head to tail and then flip coin 4 from tail to head. Result will be:
```
1  2  3  4  5  6  7  8  9 10 11 12 13
0  2  0  4  5  0  0  0  0 10  0 12  0
```
But from the point of nim game, piles before (2,5,9,10,12) and piles after (2,5,4,10,12), so still valid move within nim game!

3. H->, H->T

`H->T, H->T` means that we will decrease two piles which doesn't looks like valid nim operation, but fear not. We will exploit the fact that if __two pile sizes are equal, we can ignore them__. So from example above we have nim game:
```
(2, 4, 5, 10, 12)
```
if we decide to flip from head to tail coin 10 and 4 we can actually make 10 equal to 4:
```
(2, 4, 5, 4, 12)
```
ultimately this is same position as with both 4 set to 0. So again this is valid nim move.

This all means that representation chosen (with setting pile sizes to coin index if coin is on head), leads to valid nim game.

__2D Nim__

This game is played exactly as Nimble but on 2D checker-board. Place coins on board and players can move single coin any number of squares to the left or down (not both). Player that moves last coin to the bottom-left corner wins.

---

This is easily represented as nim game by creating two piles for each coin, for it's vertical and horizontal distance (from bottom and left respectively).

__Poker Nim__

Played as regular Nim but players can also add to the piles.

---

This does not change anything.

__Staircase Nim__

There is staircase with steps from `0` to `n`. Each step can contain some number of balls. Each player can move some balls from step `k` to `k-1`. Player who moves last ball on step `0` wins.

---

If player moves some balls from __even__ step to __odd__ step, this turn can be always reverted by moving second player same number of balls from __odd__ step to __even__ step. On the other hand when balls are moved from __odd__ step to __even__ step similar logic won't work because there can be situation when this can't be revert by second player (balls has been moved to step 0).

This can mean that balls at __even__ steps are not interesting for the game as moving them does not change the outcome. Also moving balls to __even__ step can be considered as removing the balls from the game.

Now we have nim game if only balls at __odd__ steps are considered!

# Sprague Grundy Function

## Mex

Minimal Excludant, or mex, of a set of non-negative integers is the smallest non-negative integer not in the set.
For example:
mex of set {1,2,3} is 0 and mex of set {0,1,3,4,5} is 2.

## Sprague-Grundy Function

Grundy value of position X is mex of set consisting of grundy values of positions reachable from X.

> Position with grundy value 0 is loosing position, otherwise it's winning position.

For example:

__Simple take-away game__  
Player can take 1,2 or 3 stones from pile. We will start filling in grundy values from 0 which is terminal position and has grundy value 0:
```
number of stones: 0  1  2  3  4  5  6  7  8  9 10 11 12 13 
grundy value:     0  1  2  3  0  1  2  3  0  1  2  3  0  1
```
1. from position 1 we can take only one stone reaching position 0 which has grundy value 0. So position has grundy value equal to mex of {0} which is 1
2. from position 2 we can reach positions 0 and 1 which has grundy values {0,1}
3. from position 3 we can reach positions with grundy values {0,1,2}
4. from position 4 we can reach positions 1, 2 and 3 with grundy values {1,2,3} so mex is 0
5. from position 5 we can reach positions 2, 3 and 4 with grundy values {2,3,0} so mex is 1

---

__At Least Half__  
Player can each time take at least half of the stones from pile:
```
number of stones: 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
grundy value    : 0  1  2  2  3  3  3  3  4  4  4  4  4  4  4  4  5
```
7. from 7 stones we can take 7, 6, 5 and 4 stones (at least half). This leads to positions 0, 1, 2 and 3 and set of grundy values is {0, 1, 2, 2} so grundy of 7 is 3.
8. from 8 stones we can take 8, 7, 6, 5 and 4 stones which leads to positions 0, 1, 2, 3 and 4. Set of grundy values is {0, 1, 2, 2, 3} and mex is 4.

---

__At Most Half__
Player can take at most half of the stones (but at least one). In this case also 1 is terminal position.
```
number of stones: 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16
grundy value:     0  0  1  0  2  1  3  0  4  2  5  1  6  3  7  0  8
```

# Sprague Grundy Theorem

>If there are multiple positions (multiple games played simultaneously) find grundy value for each position and take the XOR to get final combined grundy value for all positions.

If game is _misere_ form of game, theorem does not apply (see [Chalkboard XOR Game](https://leetcode.com/problems/chalkboard-xor-game/))

# Various Examples

## Tower Breakers

[HackerRank](https://www.hackerrank.com/challenges/tower-breakers-1)

```
Two players are playing a game of Tower Breakers! Player 1 always moves first, and both players always play optimally. The rules of the game are as follows:
* Initially there are n towers.
* Each tower is of height m.
* The players move in alternating turns.
* In each turn, a player can choose a tower of height x and reduce its height to y, where 1 <= y < x and y evenly divides x.
* If the current player is unable to make a move, they lose the game. 
```

Observations:  
1. If height of towers is `m = 1` then first player lose.
2. Otherwise if number of towers `n` is even first player also lose. Why? Because any move first player does is possible to replicate on some other tower ultimately leading to configuration with all heights set to 1 and first player is on the move.
3. But if number of towers `n` is odd, it can be converted to even number of towers in single move. This means that first player will always wins.

## A Chessboard Game

[HackerRank](https://www.hackerrank.com/challenges/a-chessboard-game-1)

```
Two players are playing a game on a chessboard. The rules of the game are as follows:
* The game starts with a single coin located at some (x, y) coordinates. The coordinates of the upper left cell are (1,1), and of the lower right cell are
(15, 15).
* In each move, a player must move the coin from cell (x, y) to one of the following locations:
1. (x-2, y+1)
2. (x-2, y-1)
3. (x+1, y-2)
4. (x-1, y-2)
Note: The coin must remain inside the confines of the board.
* Beginning with player 1, the players alternate turns. The first player who is unable to make a move loses the game.
```

Recursive function to compute grundy value without memoization:  
```c++
const int dx[] = { -2, -2,  1, -1 };
const int dy[] = {  1, -1, -2, -2 };

int computeGrundy(int x, int y)
{
    set<int> states;
    for (int i = 0; i < 4; i++)
    {
        int xx = x + dx[i];
        int yy = y + dy[i];

        if (xx < 1 || xx > 15 || yy < 1 || yy > 15)
            continue;
        states.insert(solve(xx, yy));
    }
    return mex(states);
}
```

## Misere Nim

[HackerRank](https://www.hackerrank.com/challenges/misere-nim-1)

```
Two people are playing game of Misère Nim. The basic rules for this game are as follows:
* The game starts with n piles of stones. Each pile some number of stones.
* The players move in alternating turns. During each move, the current player must remove one or more stones from a single pile.
* The player who removes the last stone loses the game.
```

Observations:  
1. If nim sum of initial state is 0, second player can make always the sum again 0 by his turn (note: was proven that when nim sum is zero, it must be non-zero after removing stones and if it's not zero, it can be make zero by removing some stones from single pile)
2. When the last pile is left, second player then can choose not to remove all stones but reduce the number of stones to 1. So second player wins.
3. One exception is if all piles are one stone piles. If so, winner is decided according to number of piles.

```
if all piles are one stone piles
    number of piles is even
        first player wins
    otherwise
        second player wins
if nim sum is zero
    second player wins
otherwise
    first player wins
```

## Tower Breakers Revisited

[HackerRank](https://www.hackerrank.com/challenges/tower-breakers-revisited-1)

```
Two players are playing a game of Tower Breakers! The rules of the game are as follows:
* Player 1 always moves first, and both players always move optimally.
* Initially there are N towers of various heights.
* The players move in alternating turns. In each turn, a player can choose a tower of height X and reduce its height to Y, where 1 <= Y < X and Y evenly divides X.
* If the current player is unable to make any move, they lose the game.
```

This is the same as original Tower Breakers but towers may have different heights. The key observation is that new reduced height Y must evenly divide X.

### Example 8

When thinking about this problem one has to think about prime factorization of number. For example prime factorization of 8 is:  
2 * 2 * 2 = 2^3  
what are possible heights Y for 8 ? 8 can be reduced to:  
1 = 2^0  
2 = 2^1  
4 = 2^2  

### Example 30

Another example is 30  
2 * 3 * 5 = 2^1 * 3^1 * 5^1  
possible heights Y for 30:  
1  = 2^0 * 3^0 * 5^0  
2  = 2^1 * 3^0 * 5^0  
6  = 2^1 * 3^1 * 5^0  
3  = 2^0 * 3^1 * 5^0  
15 = 2^0 * 3^1 * 5^1  

### Solution

From examples it is clear that number Y which evenly divides number X has the same prime factors but only raised to different powers. In this case number Y is strictly smaller than X so it has less powers (take a look at examples above!)

This means that this problem can be converted to nim game when the powers of primes are piles which are being decremented. Reducing number X to Y means that some powers are taken from the piles.

```c++
vector<int> sieve(int n)
{
    vector<bool> primes(n + 1, true);
    vector<int> counts(n + 1, 0);

    for (int i = 2; i <= n; i++)
    {
        if (!primes[i])
        {
            continue;
        }

        // prime has count 1
        counts[i] = 1;
        for (int j = 2 * i; j <= n; j += i)
        {
            // this jj part is about adding all i's in factorization of j
            // for example 9 is 3 * 3, we need to add both 3s
            int jj = j;
            while(jj % i == 0)
            {
                counts[j]++;
                jj /= i;
            }
            primes[j] = false;
        }
    }

    return counts;
}
```
This is a sieve that returns counts of powers for each number. For each next `j` of prime `i` we need to take into account all instances of `i` in `j`. For example in 8 there are three 2s, that means 8 is 2^3 so size of pile for 8 is 3.

## Tower Breakers Again

[HackerRank](https://www.hackerrank.com/challenges/tower-breakers-again-1)

```
Two players are playing a game of Tower Breakers! The rules of the game are as follows:
* Player 1 always moves first.
* Initially there are N towers of various heights.
* The players move in alternating turns. In each turn, a player must choose a tower of height X and break it down into Y towers, each of height Z. The numbers Y and Z must satisfy T * Z = X and Y > 1.
* If the current player is unable to make any move, they lose the game.
```

One thing to realize is that if tower is broken down into an even number of towers it will ultimately makes no difference and is equivalent as if the whole tower is removed at once. Reason for this that move on one tower can be always replicated by opponent on other tower.  
Other thing is that if tower is broken down into odd number of towers of height Z, it is equivalent as of breaking it into single tower of height Z. Argument is same as in the previous paragraph.

Pseudocode for whole algorithm is as follows:
```
for each tower
    compute grundy value G for tower
    XOR grundy value with nim sum
```

In order to compute grundy value of some tower with height Z we need to compute grundy values for all substates and take mex of those grundies:
```c++
int grundy(int tower, const vector<vector<int>>& divisors, map<int, int>& memo)
{
    if (tower == 1)
        return 0;

    if (memo.count(tower))
        return memo[tower];

    set<int> states;
    for (auto y : divisors[tower])
    {
        int z = tower / y;
        // if tower is divided into even number of smaller towers, all smaller towers cancels out
        // if tower is divided into odd number of smaller towers, all cancels out except the last one (for example in 5 four wil cancel out)
        if (y % 2 == 0)
            states.insert(0);
        else
            states.insert(grundy(z, divisors, memo));
    }

    return memo[tower] = mex(states);
}
```
In order to compute divisors of numbers we will use sieve:
```c++
vector<vector<int>> sieve(int n)
{
    vector<vector<int>> divisors(n, vector<int>());

    for (int i = 2; i < n; i++)
    {
        for (int j = i; j < n; j += i)
            divisors[j].push_back(i);
    }

    return divisors;
}
```

## Zero-Move Nim

[HackerRank](https://www.hackerrank.com/challenges/zero-move-nim/)

```
Normal Nim game. There are N piles each has some number of stones. Two players take turns removing some number of stones from single pile (at least one stone). First player who can't make move loses.

There is one more rule. For each non-empty pile, some player can make zero-move. That is in his move no stones will be removed. This move can be done only once per pile.
```

Solution here is to code brute-force recursive function to compute grundy values:
```c++
int grundy(int pile, bool hasZeroMove)
{
    if (pile == 0)
        return 0;

    set<int> states;
    for (int i = 0; i < pile; i++)
        states.insert(grundy(i, hasZeroMove));
    
    if (hasZeroMove)
        states.insert(grundy(pile, false));

    return mex(states);
}
```
When this function is run for some pile numbers output looks like this:
```
0 0
1 2
2 1
3 4
4 3
5 6
6 5
7 8
8 7
9 10
10 9
11 12
12 11
13 14
14 13
15 16
```
So the optimized grundy function that will not take forever:
```c++
int grundy2(int pile)
{
    if (pile == 0)
        return 0;

    if (pile % 2 == 0)
        return pile - 1;
    return pile + 1;
}
```
The last part is normal. We will take nimsum for all piles and if it's zero, first player will lose:
```c++
    int nimSum = 0;
    for (const auto& pile : piles)
        nimSum ^= grundy2(pile);
        //nimSum ^= grundy(pile, true);

    return nimSum == 0 ? 'L' : 'W';
```

## Digits Square Board

[HackerRank](https://www.hackerrank.com/challenges/zero-move-nim/)

```
There is NxN square board, each cells contains some number from 1 to 9.

The players move in alternating turns. In each move, the current player performs the following actions:

* Chooses a board that has at least one non-prime number written on it and has more than one cell (i.e., dimensions > 1x1).
* Cuts the chosen board into 2 smaller boards by breaking it along any horizontal or vertical line at the edge of a cell.

The game ends when there are no more cuttable boards (i.e., there are N * (1x1) boards, or all boards have only prime numbers written on them). The first player who is unable to make a move loses.
```

Key part is recursive computing of grundy values, create set and take mex of alternatives as usual. One difference is the fact that after cutting we get two boards. Both of those boards are played simultaneously so they are single game and should form single grundy value (which represents alternatives of game). So we need to take xor between those recursive calls:

```c++
    if (board.r1 == board.r2 && board.c1 == board.c2)
        return 0;

    if (!isCuttable(board, grid))
        return 0;

    set<int> states;
    for (int r = board.r1 + 1; r < board.r2; r++)
    {
        auto [board1, board2] = cutAtRow(board, r);
        states.insert(grundy(board1, grid) ^ grundy(board2, grid));
    }

    for (int c = board.c1 + 1; c < board.c2; c++)
    {
        auto [board1, board2] = cutAtCol(board, c);
        states.insert(grundy(board1, grid) ^ grundy(board2, grid));
    }

    return mex(states);
```

## Stone Division

[HackerRank](https://www.hackerrank.com/challenges/stone-division)

```
Consider the following game:
* There are two players, First and Second, sitting in front of a pile of n stones. First always plays first.
* There is a set S, of m distinct integers defined as S = { s0, s1, ..., sm-1 }.
* The players move in alternating turns. During each turn, a player chooses some s c S and splits one of the piles into exactly si smaller piles of equal size. If no si exists that will split one of the available piles into exactly si equal smaller piles, the player loses.
```

So we have some piles and set of integers. In one turn we can divide some pile into smaller piles with equal size. Division can be made using some integer from the set. For example:
We have pile with size 15 and set of integers is { 2, 3, 5 }. We can't use 2 because it does not divide 15 but we can use 3 to divide 15 into three piles of size 5 {5, 5, 5} or we can use 5 to divide 15 into five piles of size 3 {3, 3, 3, 3, 3}.

So the normal way how to approach this is to compute grundies recursively. In recursive function for pile of size N we will find all integers M that divides N without remainder. Then we will compute grundy for each smaller pile of size N / M (there will be M of them) and XOR them! Remember we need XOR-ing because all smaller piles must be played.
Here is untested code for illustration: 

```c++
int grundy(int N, const vector<int>& numbers)
{
    set<int> states;
    for (auto M : numbers)
    {
        if (N % M != 0)
            continue;
        int state = 0;
        for (int i = 0; i < M; i++)
            state ^= grundy(N / M, numbers);
        states.insert(state);
    }
    return mex(states);
}
```

This can be optimized by the following fact:
> XOR of equal numbers is zero. If we are XOR-ing numbers in chain, pair of equal numbers can be removed.

That means that there are two optimizations:
* if we divide pile into even number of smaller piles resulting grundy will be zero
* if we divide pile into odd number of smaller piles we just need to call recursive function once (for example 7 is 6 + 1, we don't need to call grundy for 6 piles because that will be zero)

```c++
int grundy(int pile, const vector<int>& numbers)
{
    set<int> states;
    for (auto n : numbers)
    {
        if (pile % n == 0)
        {
            int newPileCount = pile / n;
            if (newPileCount % 2 == 0)
                states.insert(0);
            else
                states.insert(grundy(newPileCount, numbers));
        }
    }

    return mex(states);
}
```

## Chocolate in the Box

[HackerRank](https://www.hackerrank.com/challenges/chocolate-in-box)

```
Two players are playing Nim game. Return how many winning moves the first player has.
```

First player wins if nimsum of all the piles after his first move is 0. Here is the key observation:
> Consider game with three pile {x, y, z}. If player decides to change x, his move will be winning move if and only if nimsum after his move is 0. That is if x = y ^ z (we need to have x ^ y ^ z = 0, if y ^ z is some number, x must be that number to have 0)

This implies that there is only one winning move per pile. And this winning move can be done only if `x > y ^ z` (because size of pile can be only decreased in a move).

Here is code:
```c++
int countNumberOfWaysToWin(vector<int>& boxes)
{
    int nimSum = 0;
    for (auto box : boxes)
        nimSum ^= box;

    int result = 0;
    for (auto box : boxes)
    {
        if ((nimSum ^ box) < box)
            result++;
    }
    return result;
}
```
There is one trick here. We take XOR of all the boxes and then we XOR again the particular box for which we are testing whether it can be used to make winning move. Reason for this is the following:
```
(y ^ z) = (x ^ y ^ z) ^ x
```
This means that by `nimSum ^ box` we get XOR of all the boxes except the box (which is what we need).

## Kitty and Katty

[HackerRank](https://www.hackerrank.com/challenges/kitty-and-katty)

```
There is N blocks, Kitty and Katty taking turns and Kitty is the first player. In each move:
* Take two blocks A and B and and insert new block A - B into the set
* The game ends when there is onlu one block left and the winner is determined by the number X on the last block:
** if X % 3 = 1, Kitty wins
** if X % 3 = 2, Katty wins
** if X % 3 = 0, player who moved last wins
```

So if N is equal to 1, then Kitty will win, because `1 % 3 = 1`. If N is equal to 2, then we have set { 1, 2 } and Kitty has two options:
* take A = 1 and B = 2 and resulting set after move is { -1 }
* take A = 2 and B = 1 and resulting set after move is {  1 }

> Important modulo property is that remainder cannot be zero. That means that (-2) % 3 != (2) % 3 (in first case remainder is 1 and in the second 2)

This means that Kitty will make resulting set { 1 } and will win. This also implies that when there are any two numbers left in the set { a, b } the player which is on the move will win. Either numbers are equal or player can make remainder 1 or 2 taking either { a - b } or { b - a } (result is always x or -x).

```c++
string decideWinner(int n)
{
    if (n == 1)
        return "Kitty";
    
    if (n % 2 == 0)
        return "Kitty";
    return "Katty";
}
```

## Matrix Game

We have a matrix M x N, or rather vector of rows. In each turn player can take any right-most non-zero number and decrease it (at least by one, but can go down to zero like in nim game). Game ends when all numbers in all rows are zero and player who made the last move wins.

The recursive solution gave me stack overflow so I tried to find a pattern:

For single value in a row grundy value is that number. For example:
[1] - reachable state is only { [0] } so grundy([1]) is 1
[5] - reachable states are { [4], [3], [2], [1], [0] } so grundy([5]) is 5

For two values in a row:
[2, 1] - reachable state is only { [2] } so grundy([2, 1]) is 0 (because grundy([2]) is 2)
[2, 2] - reachable states are { [2,1], [2] } which has grundies { 0, 2 } so grundy([2,2]) is 1
[2, 3] - reachable states are { [2,2], [2,1], [2] } which has grundies { 1, 0, 2 } so grundy([2,3]) is 3

From this we can assume that pattern is as follows:
* for single number in a row, grundy value is that number
* otherwise
** if previous grundy value is more or equal then last number in current state, grundy of current state is last number - 1 (cases [2,1] and [2, 2] from example)
** if previous grundy value is less then last number in current state, grundy of current state is last number (case [2, 3])

What is not clear to me is what "previous grundy value" is. What you need to do is to iterate from right to left for some reason, like this:
```c++
int grundy(const vector<int>& row)
{
    int lastGrundy = row[row.size() - 1];
    for (int i = row.size() - 2; i >= 0; i--)
    {
        if (lastGrundy >= row[i])
            lastGrundy = row[i] - 1;
        else
            lastGrundy = row[i];
    }
    return lastGrundy;
}
```

## Friends Game

```
There is a tree with n nodes rooted at node 1. At each node, there is some number of stones. Each turn player must take two nodes from any node (except parent of course) and move it to any of the ancestors. Game ends when there is no move possible.
```

One observation is that grundy value of each node is it's depth. Root node has grundy 0, all it's direct childs has grundy 1 and so on. Another observation is that any node can be played independently (meaning like independent game).

The solution is to take XOR of all the stone numbers on all nodes except the root.

## Ada Pawns

```
Pawn chess is played on a long board with N squares in one row. Initially, some of the squares contain pawns.
* no two pawns can occupy the same square at the same time
* a pawn cannot jump over another pawn, i.e. if there is a pawn at square i, then it can only be moved to square i−2 if squares i−1 and i−2 are empty
* pawns cannot move outside of the board (outs are forbidden)

The players alternate turns; as usual, Ada plays first. In each turn, the current player must choose a pawn and move it either one or two squares to the left of its current position. The player that cannot make a move loses.
```

This can be seen as a staircase nim. Number of free squares in front of pawn can be seen as a size of pile. For example:
```
...P..P.P
```
can be seen as staircase nim with 3, 2 and 1 piles. If some pawn will move, it will decrease pile to the left and increase pile to the right.
> Similarly as in staircase nim, piles at even positions (starting from right) are not significant and should be ignored.

> Also the grundy number of pile N is N % 3 because maximum 2 stones can be removed

```c++
string solve(string board)
{
    vector<int> piles;
    int pile = 0;
    for (int i = 0; i < board.size(); i++)
    {
        if (board[i] == 'P')
        {
            piles.push_back(pile);
            pile = 0;
        }
        else
        {
            pile++;
        }
    }

    reverse(begin(piles), end(piles));

    int nimSum = 0;
    for (int i = 0; i < piles.size(); i += 2)
    {
        nimSum ^= (piles[i] % 3);
    }

    return nimSum == 0 ? "No" : "Yes";
}
```

## Grundy's Game

```
Grundy's game is a two-player mathematical game of strategy. The starting configuration is a single heap of objects, and the two players take turn splitting a single heap into two heaps of different sizes. The game ends when only heaps of size two and smaller remain, none of which can be split unequally. The game is usually played as a normal play game, which means that the last person who can make an allowed move wins. 
```

Grundy value of some heap N is mex of all the states reachable from N. For example for N = 5:
from 5 we can go to {(4 1), (3 2)} so grundy value G(5) = mex({ G(4 1), G(3 2) }). When recursively computing grundies we will XOR games which are being played in parallel:

```c++
int grundy(int pile)
{
    set<int> states;
    for (int i = 1; i <= pile / 2; i++)
    {
        if (i != pile - i)
            states.insert(grundy(i, memo) ^ grundy(pile - i, memo));
    }
    return mex(states);
}
```
Here is also DP non-recursive solution:
```c++
int grundyDp(int pile)
{
    vector<int> dp(pile + 1, 0);
    for (int i = 3; i <= pile; i++)
    {
        set<int> states;
        for (int j = 1; j <= i / 2; j++)
        {
            states.insert(dp[j] ^ dp[i - j]);
        }
        dp[i] = mex(states);
    }
    return dp[pile];
}
```

## A Lot of Games

```
The game with strings for two players.

Given a group of n non-empty strings. During the game two players build the word together, initially the word is empty. The players move in turns. On his step player must add a single letter in the end of the word, the resulting word must be prefix of at least one string from the group. A player loses if he cannot move.

Andrew and Alex decided to play this game k times. The player who is the loser of the i-th game makes the first move in the (i + 1)-th game. Guys decided that the winner of all games is the player who wins the last (k-th) game.
```

First part is about deciding whether it is possible to win for starting player. This can be done in a trie using win/lose positions (W/L). Here is an example:
```
ahoj
ahmad
ahula
aholi

trie:
            a
            |
            h
         /  |  \
        o   u   m
       / \  |   |
      j  l  l   a
         |  |   |
         i  a   d

W means we can win if we want
L means we will lose for sure
            L
            |
            W
         /  |  \
        W   L   L
       / \  |   |
      L  W  W   W
         |  |   |
         L  L   L
```
W/L are filled in recursively from bottom-up. Leaf nodes are `L` values so for leafs `{j, i, a, d}` we have L, then for each parent (for which W/L values are known for all childs) we say:

> parent is W if at least one child is L, otherwise parent is L

This way we will determine whether it is possible to win, but in order to solve this we need to determine also whether it is possible to lose because actually loosing is the way for winning in this game.

To determine whether it is possible to lose we will again start from leaf nodes:
```
A - means we can lose if we want
B - means we will win for sure

            A
            |
            B
         /  |  \
        A   A   A
       / \  |   |
      A  B  B   B
         |  |   |
         A  A   A
```

> parent is A if at least one of the child is B

The last is about determining winner or loser after K games. It is easy if we have `canWin` and `canLose` information (this is W/L and A/B value for root node when the string is empty).

There are three states:
* `canWin` and `canLose`
In this case player who starts the first game will win also the last game. His winning strategy will be lose all the games except the last one (because he will always start).
* `canWin`
Now it is not in the hands of players. They can only win so winning will alternate and winner of K-th game depends on whether K is odd or even.
* `canLose`
If it is possible to only lose the game the starting player will also lose the k-th game (because he will always start).