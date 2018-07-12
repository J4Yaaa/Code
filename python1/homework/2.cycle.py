#!/usr/bin/env python
# coding=utf-8

# 1.利用 whie 循环输出 0-10
# i = 0
# while i < 11:
#     print i
#     i += 1

# 2.使用 for 循环输出 0-10
# for i in range(0,11):
#     print i

# 3.用户输入一个字符串,逐个字符显示,分别实现while和for版本
# a) for 版本
# mystr = raw_input('Please input : ')
# for c in mystr:
#     print c,
# b) while 版本
mystr = raw_input('Please input : ')
c = 0
while c < len(mystr):
    print mystr[c]
    c += 1

