# Perform String Shifts

You are given a string s containing lowercase English letters, and a matrix shift, where shift[i] = [direction, amount]:

direction can be 0 (for left shift) or 1 (for right shift). 
amount is the amount by which string s is to be shifted.
A left shift by 1 means remove the first character of s and append it to the end.
Similarly, a right shift by 1 means remove the last character of s and add it to the beginning.
Return the final string after all operations.

 

Example 1:

Input: s = "abc", shift = [[0,1],[1,2]]
Output: "cab"
Explanation: 
[0,1] means shift to left by 1. "abc" -> "bca"
[1,2] means shift to right by 2. "bca" -> "cab"
Example 2:

Input: s = "abcdefg", shift = [[1,1],[1,1],[0,2],[1,3]]
Output: "efgabcd"
Explanation:  
[1,1] means shift to right by 1. "abcdefg" -> "gabcdef"
[1,1] means shift to right by 1. "gabcdef" -> "fgabcde"
[0,2] means shift to left by 2. "fgabcde" -> "abcdefg"
[1,3] means shift to right by 3. "abcdefg" -> "efgabcd"
 

Constraints:

1 <= s.length <= 100
s only contains lower case English letters.
1 <= shift.length <= 100
shift[i].length == 2
0 <= shift[i][0] <= 1
0 <= shift[i][1] <= 100

## solution

这就是一个循环左移和右移的问题，循环左移时，把最左边一位拿出来，放在末尾即可，循环右移时把最后一位拿出来，放在开头即可

```python
class Solution:
    def stringShift(self, s: str, shift: List[List[int]]) -> str:
        lst=list(s)
        for i in range(len(shift)):
            for j in range(shift[i][1]):
                if shift[i][0] == 1:
                    tmp=lst[len(lst)-1]
                    lst.pop()
                    lst.insert(0,tmp)
                else:
                    tmp=lst[0]
                    lst.remove(lst[0])
                    lst.append(tmp)
        return "".join(lst)
```

分析：
时间复杂度：O(N)；N为移动的次数
空间复杂度：O(1)

## 参考链接

[leetcode](https://leetcode.com/explore/challenge/card/30-day-leetcoding-challenge/529/week-2/3299/)
