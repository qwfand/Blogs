# 2021面试准备

## os

进程vs线程

process：是对运行时程序的封装，是系统资源调度和分配的基本单位，实现了操作系统的并发

thread：进程的子任务，是CPU调度和分派的基本单位，用于保证程序的实时性，实现进程内部的并发

占有一个虚拟处理器，独自的寄存器组

死锁必要条件

1. 互斥
2. 占有且等待
3. 不可抢占
4. 循环等待

死锁避免-资源分配拒绝
银行家算法

## 网络

浏览器中输入url回车后发生了什么

1. URL 解析

2. DNS 查询

3. TCP 连接

4. 处理请求

5. 接受响应

6. 渲染页面

[l](https://www.cnblogs.com/jin-zhe/p/11586327.html)

TCP和UDP的区别

DNS解析的过程

## 算法

树的直径
543. Diameter of Binary Tree

判断链表元素是否回文，要求空间复杂度O(1)
234. Palindrome Linked List

判断完全二叉树
958. Check Completeness of a Binary Tree

单调栈：
[blog](https://blog.csdn.net/lucky52529/article/details/89155694)
