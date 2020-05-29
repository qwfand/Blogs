# letcode1143 Longest Common Subsequence

Longest Common Subsequence
Given two strings text1 and text2, return the length of their longest common subsequence.

A subsequence of a string is a new string generated from the original string with some characters(can be none) deleted without changing the relative order of the remaining characters. (eg, "ace" is a subsequence of "abcde" while "aec" is not). A common subsequence of two strings is a subsequence that is common to both strings.

If there is no common subsequence, return 0.

Example 1:

Input: text1 = "abcde", text2 = "ace"
Output: 3  
Explanation: The longest common subsequence is "ace" and its length is 3.
Example 2:

Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.
Example 3:

Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.

Constraints:

1 <= text1.length <= 1000
1 <= text2.length <= 1000
The input strings consist of lowercase English characters only.
   Hide Hint #1  
Try dynamic programming. DP[i][j] represents the longest common subsequence of text1[0 ... i] & text2[0 ... j].
   Hide Hint #2  
DP[i][j] = DP[i - 1][j - 1] + 1 , if text1[i] == text2[j] DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]) , otherwise

## solution

### approach1 dp

```c++
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int a=text1.length();
        int b=text2.length();
        int dp[a+1][b+1];
        for(int i =0;i<a;i++)
            for(int j=0;j<b;j++)
            {
                if(i==0)
                {
                    if(text2.find(text1[0])<=j)
                        dp[i][j]=1;
                    else
                        dp[i][j]=0;
                    continue;
                }
                if(j==0)
                {
                    if(text1.find(text2[0])<=i)
                        dp[i][j]=1;
                    else
                        dp[i][j]=0;
                    continue;
                }
                if(text1[i] == text2[j])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        return dp[a-1][b-1];
    }
};
```

## 参考链接

[lletcode](https://leetcode.com/problems/longest-common-subsequence/)
