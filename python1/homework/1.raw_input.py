#!/usr/bin/env python
# coding=utf-8

# 1.使用raw_input从用户输入得到一个字符串,并显示用户从输出的内容
# mystr = raw_input('Enter str : ')
# print 'str is ' + mystr

# 2.使用raw_input输入两个数字,计算两个数字并显示 
# raw_input返回的结果只是一个字符串.
# 如果需要获得一个数字, 需要使用int函数把字符串转换成数字.

# a)最简单的读法
# num1 = raw_input('Enter num1 : ')
# num2 = raw_input('Enter num2 : ')

# b)一次读取多个值
# num1,num2 = raw_input('Enter two number : ').split()
# sumnum = int(num1) + int(num2)

# c)上面读取的都是字符串,如果想直接读取整数,可以使用map
num1,num2 = map(int,raw_input('Enter two numbers: ').split())
sumnum = num1 + num2

# 格式化输出
print "sumnum = %d" % sumnum
