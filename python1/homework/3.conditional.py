#!/usr/bin/python
# coding=utf-8

# 用户输入一个数字,判断这个数字是正数,负数还是0
num = raw_input('Enter a number: ')
if int(num) == 0:
    print 'Zero'
elif int(num) > 0:
    print 'Positive'
else:
    print 'Negative'
