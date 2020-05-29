# leetcode 49. Group Anagrams

Given an array of strings, group anagrams together.

Example:

Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
Note:

All inputs will be in lowercase.
The order of your output does not matter.

## solutions

此道题目是把由字母颠倒顺序构成的单词归类到一起

### Approach 1

首先想到了，处理两个单词是否可以贵为一类，于是有了IS函数，根据Is函数写了两种方法，但是最后一个case都超时了；

```python
class Solution:
    def Is(self,str1, str2):
        lst1 = list(str1)
        lst2 = list(str2)
        lst1.sort()
        lst2.sort()
        return lst1 == lst2

    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        lst=[[strs[0]]]
        for i in range(1,len(strs)):
            find = False
            for j in range(len(lst)):
                if self.Is(strs[i],lst[j][0]):
                    lst[j].append(strs[i])
                    find = True
                    break
            if not find:
                lst.append([strs[i]])
        lst.reverse()
        return lst
```

```python
class Solution:
    def Is(self,cmplst, str2, i):
        lst2 = list(str2)
        lst2.sort()
        return cmplst[i] == lst2

    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        lst=[[strs[0]]]
        tmp=list(strs[0])
        tmp.sort()
        cmplst=[tmp]
        for i in range(1,len(strs)):
            find = False
            for j in range(len(lst)):
                if self.Is(cmplst,strs[i],j):
                    lst[j].append(strs[i])
                    find = True
                    break
            if not find:
                lst.append([strs[i]])
                tmp=list(strs[i])
                tmp.sort()
                cmplst.append(tmp)
        #lst.reverse()
        return lst
```

### Approach 2 Categorize by Sorted String

用一个排好序的字母顺序作为 key，其值为对应的单词：
如：dictionary={('a','e','t'):["eat","ate"]}

```python
class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        ans=collections.defaultdict(list)
        for s in strs:
            ans[tuple(sorted(s))].append(s)
        return ans.values()
```

分析：
时间复杂度：O(NKlogK)；外循环为N个单词，每个单词都要根据字母序排序，假设最长的单词的长度为K，其排序时间为KlogK
空间复杂度：O(NK)；

### Approach 2: Categorize by Count

两个单词要是变位词，其每个字母的个数必须相等，用26个字母的个数作为字典的key

```python
class Solution:
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        ans=collections.defaultdict(list)
        for s in strs:
            count=[0]*26
            for char in s:
                count[ord(char)-ord('a')] += 1
            ans[tuple(count)].append(s)

        return ans.values()
```

分析：
时间复杂度：O(NK)；外循环为N个单词，每个单词都要根据字母序排序，假设最长的单词的长度为K
空间复杂度：O(NK)；

## 参考资料

[leetcode](https://leetcode.com/problems/group-anagrams/)
