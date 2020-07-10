# 单调栈

单调递增栈：出栈后元素单调递增，栈中元素则递减
单调递减栈：出栈后元素单调递减，栈中元素则递增

```c++
//单调递增栈
stack<int> st;
int[] A;

for element in A
    if stack is empty or st.top() > element:
        push(element)
    else:
        while stack is not empty and st.top() < element:
            pop()
        push(element)

```

eg：
A=[10,6,7,4]
10 -> stack=[10]
6  -> stack=[10,6]
7  -> 7>6 pop stack=[10,7]
4  -> stack=[10,7,4]

## 应用

### [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/)

```c++
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        //维护一个递减栈，加一个-1在末尾，所有元素都可以出栈
        heights.push_back(-1);
        int i, tmp, max, top;
        stack<int> st;
        i=tmp=max=0;
        for(i=0;i<heights.size();i++)
        {
            if (st.empty()||heights[st.top()]<=heights[i])
                st.push(i);
            else
            {
                while(!st.empty() && heights[st.top()] > heights[i])
                {//栈中递增
                    top=st.top();
                    st.pop();
                    tmp=(i-top)*heights[top];
                    max=tmp>max?tmp:max;
                }
                //把前面大的数改为位置 i 处较小的数,同时把下标push，这样就可以计算高度为2的
                //矩形，也可以计算高度为1的矩形
                //eg :
                //st  :   0   2   4 5 
                //height1:1 1 2 6 2 3
                //height :2 1 5 6 2 3
                // pop 5 -> tmp (i-5)*3
                // pop 4 tmp 
                //不理解下面两句的话，按照例子走一遍就明白了，我是想不到怎么巧妙的办法，只能是看完拍手称道，妙啊，厉害啊
                st.push(top);
                heights[top]=heights[i];
            }
        }
        return max;
    }
};
```

我这种凡夫俗子，只能给出O(N^2)的方法

```python
class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        maxRec=0
        tmp=0
        for i in range(len(heights)):
            for p in range(i,-1,-1):
                if heights[p]>=heights[i]:
                    p-=1
                else:
                    break
            for q in range(i,len(heights)):
                if heights[q]>=heights[i]:
                    q+=1
                else:
                    break
            #print(p,q)
            tmp=heights[i]*(q-p-1)
            if tmp>maxRec:
                maxRec=tmp
        return maxRec
```

### [496. Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/)

递增栈

```python
class Solution:
    def nextGreaterElement(self, nums1: List[int], nums2: List[int]) -> List[int]:
        dic,stack=dict(),list()
        for i in nums2:
            while stack and stack[-1] < i:#栈中元素递减
                dic[stack.pop()]=i
            stack.append(i)
        return [dic.get(i,-1) for i in nums1]
```

### [503. Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/)

和上一题没区别，循环数组，有重复元素，stack里存放index和value的tuple即可

```python
class Solution:
    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        nums=nums+nums
        dic, stack = dict(), list()
        
        for i in range(len(nums)):
            while stack and stack[-1][1] < nums[i]:
                dic[stack.pop()] = nums[i]
            stack.append((i,nums[i]))
        
        return [dic.get((i,nums[i]),-1) for i in range(len(nums)//2)]
```

or 不使用字典，使用list记录

```python
class Solution:
    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        stack, maxlen = list(), len(nums)
        res=[-1]*maxlen
        
        for i in range(maxlen*2):
            while stack and nums[stack[-1]] < nums[i%maxlen]:
                res[stack.pop()]=nums[i%maxlen]
            stack.append(i%maxlen)
        return res
```

### [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/)

和下一个最大的数字相同的思路

```python
class Solution:
    def dailyTemperatures(self, T: List[int]) -> List[int]:
        stack = list()
        
        res=[0]*len(T)
        
        for i in range(len(T)):
            while stack and T[stack[-1]] < T[i]:
                top=stack.pop()
                res[top]=i-top
            stack.append(i)
        return res
```

### [901. Online Stock Span](https://leetcode.com/problems/online-stock-span/)

从当前位置开始，往后，多少个元素小于等于自己

```python
class StockSpanner:

    def __init__(self):
        self.stack = []

    def next(self, price):
        """
        :type price: int
        :rtype: int
        """
        res = 0
        # 栈中递减
        while len(self.stack) and self.stack[-1][0]<=price:
            res += self.stack.pop()[1]
        self.stack.append([price,res+1])
        return res + 1
# Your StockSpanner object will be instantiated and called as such:
# obj = StockSpanner()
# param_1 = obj.next(price)
```

### [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)

```python
class Solution:
    def trap(self, height: List[int]) -> int:
        stack = []
        res=0
        for i in range(len(height)):
            print(stack)
            print(i)
            while stack and height[i] > height[stack[-1]]:
                top = stack.pop()
                if not stack :
                    break
                dist = i - stack[-1] - 1
                boundryHeight = min(height[i],height[stack[-1]]) - height[top]
                #print(dist,boundryHeight)
                res += boundryHeight*dist

            stack.append(i)
        return res
```

![img](https://raw.githubusercontent.com/qwfand/Blogs/master/docs/algorithm/leetcode/stack/Trapping%20Rain%20Water.jpg)

[others](https://blog.csdn.net/qq_17550379/article/details/86519771?utm_medium=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase&depth_1-utm_source=distribute.pc_relevant_t0.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase)
