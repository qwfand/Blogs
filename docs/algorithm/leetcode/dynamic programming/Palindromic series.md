# palindromic Series

## 516. Longest Palindromic Subsequence

求字符串中最长的回文子串，子串不一定要连续

dp[left][right] ::= left to right 最长的的子串的长度
dp[1][len] 即为答案

dp[left][right]= dp[left+1][right-1] + 2 if s[left]==s[right]
&emsp;&emsp; =max(dp[left+1][right],dp[left][right-1]) if s[left] != s[right]

答案在右上角，注意dp填表顺序

```python
class Solution:
    def longestPalindromeSubseq(self, s: str) -> int:
        n = len(s)
        dp = [[0] * n for _ in range(n)]
        
        #右下角开始填表
        for i in range(n-1, -1, -1):
            dp[i][i] = 1
            for j in range(i+1, n):
                if s[i] == s[j]:
                    dp[i][j] = dp[i+1][j-1] + 2
                else:
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1])
        return dp[0][n-1]
```

or

```python
class Solution:
    def longestPalindromeSubseq(self, s: str) -> int:
        n=len(s)
        dp=[[0 for i in range(n+1)] for j in range(n+1)]
        
        
        # dp[i][j] is the max length of  palindromic from s[i] to s[j]
        for i in range(1,n+1):
            dp[i][i]=1
    
        for d in range(1,n):
            for left in range(1,n-d+1):
                right=left+d  #n-d+1+ (n-1)=
                if left!=right:
                    if s[left-1]==s[right-1] :
                        dp[left][right]=dp[left+1][right-1]+2
                    else:
                        dp[left][right]=max(dp[left+1][right],dp[left][right-1])
                         
        return dp[1][n]
```

[leetcode 516. Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/)

## 647. Palindromic Substrings

求字符串中回文子串的个数（连续）

### dp solution

dp[i][j] = 1: 字符串从下标i到j是回文，=0，不是回文

dp[i][j]= 1 if dp[i+1][j-1] == 1 and s[i] == s[j]

```python
class Solution:
    def countSubstrings(self, s: str) -> int:
        n=len(s)
        res=n
        dp=[[0 for i in range(n+1)] for j in range(n+1)]
        for left in range(n,0,-1):
            dp[left][left]=1
            for right in range(left+1,n+1):
                if s[left-1] == s[right-1]:
                    if dp[left+1][right-1] or left+1 > right-1:
                        dp[left][right]=1
                        res+=1
        return res
```

or 

```python
class Solution:
    def countSubstrings(self, s: str) -> int:
        n=len(s)
        cnt=n
        
        # dp[i][j]=1 s[i] to s[j] is palindromic
        for i in range(1,n+1):
            dp[i][i]=1
            #dp[0][i]=1
        for d in range(1,n):
            for left in range(1,n-d+1):
                right=left+d  #n-d+1+ (n-1)=
                if left!=right:
                    if s[left-1]==s[right-1] and (dp[left+1][right-1]==1 or right-1 < left+1):
                        dp[left][right]=1
                        cnt+=1
        
        return cnt
```

### Expand Around Center 

### Manacher's Algorithm



[647. Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/)