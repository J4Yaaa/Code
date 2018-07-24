#!/usr/bin/env python
# coding=utf-8

# 去除重复的字符,且字符串顺序不变

from collections import OrderedDict

while True:
    try:
        foo = raw_input()
        print "".join(OrderedDict.fromkeys(foo))
    except:
        break
