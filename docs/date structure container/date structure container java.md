# JAVA 常用容器集实现原理

Java的容器分为两类，一类为Collection，另一类为Map。

## MAP

map类容器都实现了Map<K, V>接口

### HashMap

1. 基于hash实现的
2. 底层为数组+链表+红黑树
3. 允许key、value为NULL
4. 线程不安全
5. 初始化时capacity=16，load factor 为0.75


### HashTable

1. 基于hash实现的
2. 同HashMap
3. 不允许NULL
4. 线程安全，每个方法都有synchronized修饰，锁定的是整张表
5. 初始化capacity=11，load factor =0.75

### ConcurrentMap

加锁机制不同，jdk1.7 分段锁---根据索引找到段号，加锁
以后粒度更细，以每个数组索引为锁来进行实现

### 总结

线程安全首先ConcurrentHashMap
单线程选HashMap


## 参考

[java 官方文档](https://docs.oracle.com/javase/8/docs/api/java/util/Collection.html)
[java 教程](https://docs.oracle.com/javase/tutorial/collections/interfaces/map.html)
