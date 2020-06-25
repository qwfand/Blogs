# C++常用容器集实现原理

## 1. 数组

数组我们最常见的老朋友了，其特性谁不知道，出来挨打；但是`int a[1000]`这样的数组容易把堆栈搞炸了，数量太大的数组建议使用`malloc`;

## 2. queue

FIFO:first-in first-out

他的标准container可以是deque 和 list，默认deque

## 3. priority_queue

优先队列（heap），root的元素要么最大或最小

默认使用vector实现

## 4. deque（double-end-queue）

序列容器，动态容量，可以在front和back增加删除元素
高效删除和添加
不保证存储空间连续（下标访问可能会出错）

实现：动态分段数组

## 5. forward_list

单向列表，只可在front增删，一颗指针指向下一个元素

## 6. list

Doubly linked list,两颗指针，一颗向前，一颗朝后

## 7. vector

动态数组，地址连续，可以像数组一样访问
通常会多分配一些空间，满了需要重新分配

## 8. stack

LIFO：last-in first-out

标准容器类vector、deque、list都满足要求，默认使用deque

## 9. map

存储<key,value>键值对
key用来排序和唯一标识对象

使用二叉搜索树实现

multimap的key可以重复

## 10. set

指定顺序存储唯一元素（无重复），元素存好之后不可修改，但可以增加删除

使用二叉搜索树实现

multiset 可以重复

## 11. unordered_map

基于hash实现的map

## 12. unordered_set

基于hash实现的set

## 相关链接

[deque](https://blog.csdn.net/qq_32378713/article/details/79415764)

[cplusplus-deque](http://www.cplusplus.com/reference/deque/deque/)
