#!/usr/bin/env python
# coding=utf-8

###########################################
# Python序列和字典
###########################################

# 序列
# 包含多个元素,且和顺序有关 (eg: 'abc'和'cba'是两个字符串)

# 字符串 / 元祖 / 列表 共同点
# 1.标准类型操作符 > < >= <= != == 

# 2. a)序列类型操作符 in/not in
#      a = ['a','b','c']
#      print 'b' in a
#    b)连接操作 +
#      a = [1,2,3]
#      b = [4,5,6]
#      print a+b # 会产生一个新的对象

#      a = [1,2,3]
#      b = [4,5,6]
#      a.extend(b) # 在原有基础上拼接,extend类似于vector的push_back
#      print a
#    c)重复操作符
#      a = [1,2,3]
#      print a*3

# 3.序列切片操作
#   [] [:] [::]
#   a = [1,2,3,4,5,6]
#   for i in range(0,len(a)):
#       print a[i]
#   
#   print a[0:-3]
#   print a[:-3]
#   
#   print a[::2]

#   字符串反转
#   a = 'abcdef'
#   print a[::-1]
