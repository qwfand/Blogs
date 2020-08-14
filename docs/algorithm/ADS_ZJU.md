# ADS in zju

It's a sad story about my ads studing in zju.  
But I think that ads is very useful and interesting, so I want to record what I hava learned in 19-20 Spring-Summer semester.

## Advanced Data Structure

### Advanced Search Structure

Kernel problem: search tree balance, reduce the height of the tree

#### AVL

AVL tree:概念，节点数与层次关系
四种平衡方法以及判别方法

#### Splay Tree

概念：
操作：zig-zag、zig-zig

#### Red-Black Tree

the number of black nodes is same，红色节点给予调整的余地

#### B+ Tree

M order B tree
- The root is either a leaf or has between 2 and M children
- All nonleaf nodes(except the root) hava between [M/2] and M children
- All leaves are at the same depth

- All data are stored at the leaves.
- Contained in each interior node are pointers P1,P2,...,Pm to the children, and k1,k2,...,Km-1, representing the smallest key found in the subtrees P2,P3,...,Pm-1, respectively.

节点不满足要求，则split

#### Inverted File Index

文档分析、结果排序、概念、数据结构设计思想、评价

### Advanced Heap Structure

kernel problem：merge operation
Binary tree representation

#### Leftist Heap

order property and structure property

merge based on the right path，time complexity

insert and delete based on merge 

#### Skew Heap

amortized cost
merge ：unconditional swap

#### Binomial queue

Bi tree，compare to the binary number

merge 实现，二进制数的相加

## Algorithms and Analysis

### Algorithn Design Techniques

#### Basic Technique

##### Greedy

Main Ideas：解决问题分成若干步，每一步都选择最优解

Typical problems：

- Activity Selection Problem：earliest finish first
- Huffman codes
    不等长编码

##### Divide and Conquer

Main Idea：把大问题分成小问题，递归解决，再合并
Running time：Substitution method，Recursion-tree method，Master method
Typical problem：
- quick、merge sort；
- closet points

##### Dynamic Programming

Main Idea：top-down analysis（reduce the complexity） and bottom-up implementation
Typical problems：
- Ordering Matrix Multiplications
- Optimal binary search tree
- All-pairs shortest path
- product assembly

##### Backtracking

Main Idea：exhaustive search + elimination
Typical Problems：
- 8-queens
- Turnpike Reconstruction
- Game Tree：α pruning，β pruning

#### Techniques for Optimization Problems

##### Approximation Methods

Main idea：find near-optimal solutions in polynomial time，Approximation Ratio
Typical problems：
- Bin packing：online，offline，next、best、first fit
- Knapsack Problem： fractional vs 0/1
- K-center

##### Local Search 

Main idea：local（define neighborhoods），search
Typical problems：
- vertex cover problem
- Hopfield Neural networks
- Maximum cut problem

#### Others

##### Randomized Algorithms

Main idea： make random decisions
Typical problem：
- Hiring problem：Permute array， online hiring（k=e/N）
- Quicksort：at least N/4，the expected number of iteration is at most 2

##### Parallel Algorithms

Main idea：Pardo for multi-processors
- Parallel Random Access Machine（PRAM） ，Work-Depth（WD）
- To resolve Access conflict：EREW、CREW、CRCW
- complexity：W(n) operations and T(n) time

Typical problems：
- Summation Problem
- Prefix-Sums
- Merging problem
- Maximum Finding

##### External Sorting

### Analysis Techniques

#### NPC

undecidable problem
decidable problem：NP problem、NP-complete


#### Amortized Analysis
