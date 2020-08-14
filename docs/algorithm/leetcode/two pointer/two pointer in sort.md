# Two Pointers in Sort

## 75. Sort Colors

Given an array with n objects colored red, white or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

example:
Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
[leetcode](https://leetcode.com/problems/sort-colors/)

利用双指针排序，其实是用两个指针来分割
使用三个指针red，white，blue
其中red左边的元素为red（值为0），white左边的元素为white（值为1），blue右边的元素为blue值为（2）
首先将red和white指针放在开头，blue放在末尾，开始移动white指针：
1. 如果white处的值为0，则和red处的值交换，red++，white++
2. 如果white处的值为1，white++
3. 如果white处的值为2，和blue处交换，blue--

```python
class Solution:
    def sortColors(self, nums: List[int]) -> None:
        red, white, blue = 0, 0, len(nums) - 1
        while white <= blue:
            if nums[white] == 0:
                nums[white], nums[red] = nums[red], nums[white]
                white += 1
                red += 1
            elif nums[white] == 2:
                nums[white], nums[blue] = nums[blue], nums[white]
                blue -= 1
            else:
                white += 1
```

也可以采用计数的方式来处理

```python
class Solution:
    def sortColors(self, nums: List[int]) -> None:
        red = white = blue = 0
        for i in nums:
            if i == 0:
                red += 1
            elif i == 1:
                white += 1
            else :
                blue += 1
        for i in range(0,red):
            nums[i] = 0
        for i in range(red, red + white):
            nums[i] = 1
        for i in range(red + white, len(nums)):
            nums[i] = 2
```
