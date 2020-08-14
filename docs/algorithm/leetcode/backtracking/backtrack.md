# BackTracking Series

## 17. Letter Combinations of a Phone Number

```python
class Solution:
    def letterCombinations(self, digits: str) -> List[str]:
        dic={}
        dic['2'] = ['a','b','c']
        dic['3'] = ['d','e','f']
        dic['4'] = ['g','h','i']
        dic['5'] = ['j','k','l']
        dic['6'] = ['m','n','o']
        dic['7'] = ['p','q','r','s']
        dic['8'] = ['t','u','v']
        dic['9'] = ['w','x','y','z']
        def backtrack(res,combination,next_digits):
            if len(next_digits) == 0:
                res.append(combination)
            else:
                for letter in dic[next_digits[0]]:
                    # append the current letter to the combination
                    # and proceed to the next digits
                    tmp=combination + letter
                    backtrack(res,tmp,next_digits[1:])
        res=[]
        if digits:
            backtrack(res,"",digits)
        return res
```

## 46. Permutations

```python
class Solution:
    def permute(self, nums: List[int]) -> List[List[int]]:
        def backtrack(nums,tmp,res):
            if len(tmp) == len(nums):      #符合要求
                res.append(tmp[:])
            else:
                for i in range(len(nums)):
                    if nums[i] in tmp:     #判断当前元素是否已经在tmp中
                        continue
                    tmp.append(nums[i])
                    backtrack(nums,tmp,res)
                    tmp.pop()               #回溯
        res = []
        tmp = []
        backtrack(nums,tmp,res)
        return res
```

## 47. Permutations II

和上一题相比，这一题可以有重复的数字，关键是去重

```python
class Solution:
    def permuteUnique(self, nums: List[int]) -> List[List[int]]:
        def backtrack(res,tmp,nums,used):
            if len(nums) == len(tmp):
                res.append(tmp[:])
            else:
                for i in range(len(nums)):
                    if used[i] or (i > 0 and used[i-1] and nums[i-1] == nums[i]):
                        continue
                    tmp.append(nums[i])
                    used[i] = True
                    backtrack(res,tmp,nums,used)
                    used[i] = False
                    tmp.pop()
        res = []
        tmp = []
        nums.sort()
        used = [False]*len(nums)
        backtrack(res,tmp,nums,used)
        return res
```

## 78. Subsets

```python
class Solution:
    def subsets(self, nums: List[int]) -> List[List[int]]:
        def backtrack(res,tmp,start):
            #if start > len(nums):
            #    return
            res.append(tmp[:])
            for i in range(start,len(nums)):
                tmp.append(nums[i])
                backtrack(res,tmp,i+1)
                tmp.pop()
        res = []
        tmp = []
        backtrack(res,tmp,0)
        return res
```

## 90. Subsets II

```python
class Solution:
    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:
        def backtrack(res,tmp,start):
            #print(tmp,start)
            res.append(tmp[:])
            for i in range(start,len(nums)):
                if i > start and nums[i-1] == nums[i]:
                    continue
                tmp.append(nums[i])
                backtrack(res,tmp,i + 1)
                tmp.pop()
                
        res = []
        tmp = []
        nums.sort()
        backtrack(res,tmp,0)
        return res
```


## 39. Combination Sum

```python
class Solution:
    def combinationSum(self, candidates: List[int], target: int) -> List[List[int]]:
        def backtrack(res,tmp,start,remain):
            #print(tmp,start,remain)
            if remain < 0:
                return
            elif remain == 0:
                res.append(tmp[:])
            else:
                for i in range(start,len(candidates)):
                    tmp.append(candidates[i])
                    backtrack(res,tmp,i,remain- candidates[i]) # not i+1 we reuse  candidates[i]
                    tmp.pop()
                    
        res = []
        tmp = []
        backtrack(res,tmp,0,target)
        return res
```

## 40. Combination Sum II

每个数字值可以使用一次

```python
class Solution:
    def combinationSum2(self, candidates: List[int], target: int) -> List[List[int]]:
        def backtrack(res,tmp,start,remain):
            if remain < 0:
                return 
            elif remain == 0:
                res.append(tmp[:])
            else:
                for i in range(start,len(candidates)):
                    if i > start and candidates[i] == candidates[i-1]:
                        continue
                    tmp.append(candidates[i])
                    backtrack(res,tmp, i+1, remain - candidates[i])
                    tmp.pop()
                    
        res = []
        tmp = []
        candidates.sort()
        backtrack(res,tmp,0,target)
        return res
```

## 216. Combination Sum III

```python
class Solution:
    def combinationSum3(self, k: int, n: int) -> List[List[int]]:
        def backtrack(res,tmp,start,remain,nums):
            #print(nums)
            if remain < 0:
                return
            elif remain == 0 and len(tmp) == k:
                res.append(tmp[:])
            else:
                for i in range(start,len(nums)):
                    tmp.append(nums[i])
                    backtrack(res,tmp,i+1,remain-nums[i],nums)
                    tmp.pop()
                    
        nums = [i for i in range(1,10)]
        #print(nums)
        res = []
        tmp = []

        backtrack(res,tmp,0,n,nums)
        return res
```

[reference](https://leetcode.com/problems/permutations/discuss/18239/A-general-approach-to-backtracking-questions-in-Java-(Subsets-Permutations-Combination-Sum-Palindrome-Partioning))


## 131. Palindrome Partitioning

```python
class Solution:
    def partition(self, s: str) -> List[List[str]]:
        def isPalindrome(s,l,r):
            while l <= r:
                if s[l] == s[r]:
                    l += 1
                    r -= 1
                else:
                    return False
            return True
        
        def backtrack(s, pos, path, res):
            print(pos,path,res)
            if pos == len(s):
                res.append(path[:])
            else:
                for i in range(pos,len(s)):
                    if isPalindrome(s,pos,i):
                        path.append(s[pos:i+1])
                        backtrack(s,i+1,path,res)
                        path.pop()
            
        pos = 0
        path = []
        res = []
        backtrack(s,0,path,res)
        return res
```

[leetcode](https://leetcode.com/problems/palindrome-partitioning/)

## 784. Letter Case Permutation

```python
class Solution:
    def letterCasePermutation(self, S: str) -> List[str]:
        def backtrack(res,lst,i):
            if i == len(lst):
                res.append("".join(lst))
                return
            else:
                backtrack(res,lst,i+1)
                if lst[i].isalpha():
                    if lst[i].islower():
                        lst[i] = lst[i].upper()
                    else:
                        lst[i] = lst[i].lower()   
                    backtrack(res,lst,i+1)
                    
        res = []
        lst = list(S)
        backtrack(res,lst,0)
        return res
```

