# Two pointer for 3 sum


## 3 sum

```python
class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        res=[]
        nums.sort()
        for i in range(len(nums)-2):
            if nums[i] > 0 :
                break
            if i > 0 and nums[i-1] == nums[i]:#alread exist
                continue
            left, right = i+1, len(nums)-1
            while left < right:
                total=nums[i]+nums[left]+nums[right]
                if total < 0:
                    left+=1
                elif total > 0:
                    right -=1
                else:
                    res.append([nums[i],nums[left],nums[right]])
                    #去重
                    while left<right and nums[left]==nums[left+1]:
                        left+=1
                    while left<right and nums[right]==nums[right-1]:
                        right-=1
                    left+=1
                    right-=1
        return res
```

## 3Sum Closest

```python
class Solution:
    def threeSumClosest(self, nums: List[int], target: int) -> int:
        diff=float('inf')
        nums.sort()
        for i in range(len(nums)):
            lo, hi= i+1, len(nums)-1
            while lo<hi:
                sum=nums[i]+nums[lo]+nums[hi]
                if abs(target-sum)<abs(diff):
                    diff= target - sum
                if sum < target:
                    lo += 1
                elif sum > target:
                    hi -= 1
                else:
                    break
            if diff == 0:
                break
        return target - diff
```

## 3sum-smaller

统计三个数的和比target小的情况的种数

```python
class Solution:
    def threeSumSmaller(self,nums,target):
        res=0
        nums.sort()
        for i in range(len(nums)):
            lo, hi= i+1, len(nums)-1
            while lo<hi:
                sum=nums[i]+nums[lo]+nums[hi]
                if sum < target:
                    res += hi - lo
                    #if (i lo hi) satisfy condition
                    # then (i lo hi-1)
                    #.....
                    #    (i,lo,lo+1) must satisfy the condition
                    #-3 -2 0 1 3
                    #i  lo     hi  ok
                    #i  lo hi      ok but skip 
                    #i  lo   hi   ok but skip

                if sum < target:
                    lo += 1
                elif sum >= target:
                    hi -= 1

        return res
```

[3sum-smaller](https://leetcode.com/problems/3sum-smaller/)