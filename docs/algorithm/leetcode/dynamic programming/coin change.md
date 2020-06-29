# DP-Coin Change

## 322. Coin Change

给出硬币的面值，和一个数量，求最少硬币的枚数。
eg：
Input: coins = [1, 2, 5], amount = 11
Output: 3 
Explanation: 11 = 5 + 5 + 1

定义dp[i]为数额为i时的最少硬币枚数，
状态转移方程为 `dp[i]=min(dp[i-COINj] + 1)` COINj为硬币的面值

```python
class Solution:
    def coinChange(self, coins: List[int], amount: int) -> int:
        dp=[0]*(amount+1)
        dp[0]=0
        for i in range(1,amount+1):
            tmp=float('inf')
            for coin in coins:
                if i - coin >=0 and dp[i-coin] + 1< tmp:
                    tmp=dp[i-coin]+1
            dp[i]=tmp
        if dp[amount] == float('inf'):
            return -1
        return dp[amount]
```

时间复杂为：O(MN) ，M为总金额，N为硬币面值的种数
空间复杂度：O(M)

[leetcode 322. Coin Change](https://leetcode.com/problems/coin-change/)

## 377. Combination Sum IV

求换硬币换法的总数，考虑顺序

eg：
nums = [1, 2, 3]
target = 4

The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)


dp[i]为数量为i的换发总数
dp[i]=sum(dp[i-Ci])  Ci为硬币面值，其中i-Ci>=0

```python
class Solution:
    def combinationSum4(self, coins: List[int], amount: int) -> int:
        dp=[0]*(amount+1)
        dp[0]=1
        for i in range(1,amount+1):
            for coin in coins:
                if i - coin >=0 :
                    dp[i] +=dp[i-coin]
            
        return dp[amount]
```

[leetcode 377. Combination Sum IV](https://leetcode.com/problems/combination-sum-iv/)
