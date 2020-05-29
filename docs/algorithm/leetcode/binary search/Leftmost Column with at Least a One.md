# leetcode Leftmost Column with at Least a One

(This problem is an interactive problem.)

A binary matrix means that all elements are 0 or 1. For each individual row of the matrix, this row is sorted in non-decreasing order.

Given a row-sorted binary matrix binaryMatrix, return leftmost column index(0-indexed) with at least a 1 in it. If such index doesn't exist, return -1.

You can't access the Binary Matrix directly.  You may only access the matrix using a BinaryMatrix interface:

BinaryMatrix.get(x, y) returns the element of the matrix at index (x, y) (0-indexed).
BinaryMatrix.dimensions() returns a list of 2 elements [n, m], which means the matrix is n * m.
Submissions making more than 1000 calls to BinaryMatrix.get will be judged Wrong Answer.  Also, any solutions that attempt to circumvent the judge will result in disqualification.

For custom testing purposes you're given the binary matrix mat as input in the following four examples. You will not have access the binary matrix directly.

Example 1:

![img](https://assets.leetcode.com/uploads/2019/10/25/untitled-diagram-5.jpg)

Input: mat = [[0,0],[1,1]]
Output: 0
Example 2:

![img](https://assets.leetcode.com/uploads/2019/10/25/untitled-diagram-4.jpg)

Input: mat = [[0,0],[0,1]]
Output: 1
Example 3:

![img](https://assets.leetcode.com/uploads/2019/10/25/untitled-diagram-3.jpg)

Input: mat = [[0,0],[0,0]]
Output: -1
Example 4:

![img](https://assets.leetcode.com/uploads/2019/10/25/untitled-diagram-6.jpg)

Input: mat = [[0,0,0,1],[0,0,1,1],[0,1,1,1]]
Output: 1
 
Constraints:

1 <= mat.length, mat[i].length <= 100
mat[i][j] is either 0 or 1.
mat[i] is sorted in a non-decreasing way.
 Hint  

1. (Binary Search) For each row do a binary search to find the leftmost one on that row and update the answer. 
2. (Optimal Approach) Imagine there is a pointer p(x, y) starting from top right corner. p can only move left or down. If the value at p is 0, move down. If the value at p is 1, move left. Try to figure out the correctness and time complexity of this algorithm.

## solution

题目是要找出最左边的、包含数字1的列，输出其列号

二分搜索

```c++
/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int x, int y);
 *     vector<int> dimensions();
 * };
 */

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        vector<int> dimension=binaryMatrix.dimensions();
        int m=dimension[0];
        int n=dimension[1];
        int leftmost=101;

        for (int i=0;i<m;i++)
        {
            int left,right,mid;
            left=0;right=n-1;
            while(left<right)
            {
                mid = (left+right)>>1;
                if(binaryMatrix.get(i,mid)==1)
                    right=mid;
                else
                    left=mid+1;
            }
            if(binaryMatrix.get(i,left)==1&&left<leftmost)
                leftmost=left;
        if(leftmost==101)
            leftmost=-1;
        return leftmost;
    }
};
```

分析：
时间复杂度：O(NlogM) N行数，M列数
空间复杂度：O(1)

## 参考链接

[leetcode](https://leetcode.com/explore/challenge/card/30-day-leetcoding-challenge/530/week-3/3306/)
