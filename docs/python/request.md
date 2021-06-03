# request

今天在MIT公开课看视频的时候，发现了有上课时候的notes，灵机一动，我想把所有的notes都拔下来，于是有了这篇blog。

```python
# coding=utf-8
import requests  # 对网页进行请求


# 打开URL，获取HTML
def openURL(URL, i):
    # 网站或许有反爬措施，所以这里进行简单的处理，将我们的爬虫伪装成是人访问
    agent = [
        'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/55.0.2883.87 Safari/537.36',
        'Mozilla/5.0 (Windows NT 10.0; WOW64; Trident/7.0; .NET4.0C; .NET4.0E; rv:11.0) like Gecko',
        'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.1 (KHTML, like Gecko) Chrome/14.0.835.163 Safari/535.1']
    headers = {
        'User-Agent': agent[2]}
    response = requests.get(URL, headers=headers)  # 对网页进行请求并返回值
    if response:
        print(URL + " 网页抓取成功")
    con = response.content
    path = './mit/lec' + str(i) + '.pdf'
    file = open(path, 'wb')
    file.write(con)
    file.close()


# begin
# 网址
ls = [i for i in range(1, 39)]
rm = [8, 17, 33]
for i in rm:
    ls.remove(i)
for i in ls:
    url = 'https://ocw.mit.edu/courses/mathematics/18-01-single-variable-calculus-fall-2006/lecture-notes/lec' + str(
        i) + '.pdf'
    openURL(url, i)

```

-[request](https://docs.python-requests.org/en/latest/api/#requests.Response)