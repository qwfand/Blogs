# power of two

判断一个数是不是2的整次方

## Iterative

```python
class Solution:
    def isPowerOfTwo(self, n: int) -> bool:
        if n <= 0:
            return False
        while n % 2 == 0 :
                n //= 2
        return n == 1
```

## bit operation

计算机中数字本身就是二进制表示的，每次乘以2，可以看成右移一位，所以2的整次方的二进制表示中必定只有一个1,而n-1则n中为1后面的位都为1
比如
&emsp;&ensp;1==>0001 0==>0000 & 0
&emsp;&ensp;2==>0010 1==>0001 & 0
&emsp;&ensp;4==>0100 3==>0011 & 0
&emsp;&ensp;8==>1000 7==>0111 & 0
&emsp;&ensp;5==>0101 4==>0100 & 0100


```python
class Solution:
    def isPowerOfTwo(self, n: int) -> bool:
        if n <= 0:
            return False
        return not (n&(n-1))
```
