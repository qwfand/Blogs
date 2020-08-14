# jvm

c/c++
malloc  -free
new delete
leak
oom

java GC
golang GC STW(停顿)
Rust

什么是垃圾

对象没有对象指向它

如何定位垃圾
1. 引用计数
    无法解决循环引用
2. 根可达算法RootSearch
    JVM stack，native method stack，
    runtime constant pool
    static reference in method
    clazz


常见的垃圾回收算法
1. mark-sweep 标记清除
    碎片
2.copying
    浪费空间
3.mark-compact
    效率低

gCollector
新时代 老年的
eden，survivor ，survivor| tenured
新生代 大量生产，大量回收，copy

新生代：老年的=1:2

new:
先放栈上
太大：放老年代 FGC （full GC）
TLAB==》Eden
Thread Local Allocation Buffer 

