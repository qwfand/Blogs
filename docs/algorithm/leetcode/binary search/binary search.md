# Binary Search

```c++
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int main()
{
    int a[10]={1,2,3,4,6,7,8,9,10,11};
    //         0 1 2 3 4 5 6 7  8  9
    int left=0,right=10;
    int target=1;
    bool find=false;

    /******************写法一*******************************/
    while(left<right)
    {
        int mid = (left+right)/2;
        printf("left %d mid %d right %d\n",left,mid,right);
        if(a[mid]==target)
        {
            printf("find at %d\n",mid);
            find = true;
            break;
        }
        if(a[mid]>target)
            right=mid;
        else
            left=mid+1;
    }
    if(!find)
        printf("not find\n");
    printf("method1 done\n");
/******************写法二***********/
    left=0,right=9;
    find=false;
    while(left<=right)
    {
        int mid = (left+right)/2;
        printf("left %d mid %d right %d\n",left,mid,right);
        if(a[mid]==target)
        {
            printf("find at %d\n",mid);
            find=true;
            break;
        }
        if(a[mid]>target)
            right=mid-1;
        else
            left=mid+1;
    }
    if(!find)
        printf("not find\n");
    printf("method2 done\n");

    left=0,right=9;
    //寻找第一个1出现的位置
    int b[10]={0,1,1,1,1,1,1,1,1,1};
    while(left<right)
    {
        int mid = (left+right)/2;
        printf("enter left %d mid %d right %d\n",left,mid,right);
        if(b[mid]==target)
        {
            printf("find at %d\n",mid);
            right=mid;
        }
        else
        {
            left=mid+1;
        }
        printf("left left %d mid %d right %d\n\n",left,mid,right);
        if (left==right)
        {
            printf("left %d \n",left);
        }
    }
    return 0;
}
```

## 找分界问题 统计1的个数

```python
'''
Input: mat = 
[[1,1,0,0,0],
 [1,1,1,1,0],
 [1,0,0,0,0],
 [1,1,0,0,0],
 [1,1,1,1,1]], 
'''
lst=[]
for i in range(len(mat)):
    left=0
    right=len(mat[i])
    while left<right:
        mid=int((left+right)/2)
        if mat[i][mid]==1:
            left=mid+1
        else:
            right=mid
    lst.append([i,left])
```

[leetcode 1337. The K Weakest Rows in a Matrix](https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/)

```python
class Solution:
    def kWeakestRows(self, mat: List[List[int]], k: int) -> List[int]:
        lst=[]
        for i in range(len(mat)):
            left=0
            right=len(mat[i])
            while left<right:
                mid=int((left+right)/2)
                if mat[i][mid]==1:
                    left=mid+1
                else:
                    right=mid
            lst.append([i,left])
        lst.sort(key=lambda x:x[1])
        res=[lst[i][0] for i in range(k)]
        return res
```

## search target

### 240. Search a 2D Matrix II

在一个每行每列都递增的矩阵中寻找一个数字

二分搜索

```python
class Solution:
    def searchMatrix(self, matrix, target):
        #n^2log(n)
        for row in range(len(matrix)):
            lo, hi = 0, len(matrix[0])
            while lo < hi:
                mid = (lo + hi) // 2
                #print(lo,hi,mid)
                if matrix[row][mid] == target:
                    return True
                elif matrix[row][mid] > target:
                    hi = mid
                else:
                    lo = mid + 1
        return False
```

右上角到左下角搜索

```python
class Solution:
    def searchMatrix(self, matrix, target):
        if not matrix:
            return False
        row, col =0, len(matrix[0]) - 1
        while row < len(matrix) and col >= 0:
            if matrix[row][col] == target:
                return True
            elif matrix[row][col] > target:#不可能在该列上面
                col -= 1
            else:#matrix[row][col] < target 不可能在该行上面
                row +=1
        return False
```
        