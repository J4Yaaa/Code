#!/usr/bin/env python
# coding=utf-8  是为了可以使中文编译过

# 变量和赋值
# myint = 10
# mystr = 'hello world'
# myfloat = 3.14
# 
# print myint
# print mystr
# print myfloat
 
# 增量赋值
# python 不支持自增长(++,--)
# myint = 10
# myint += 10
# print myint

# 静态类型(C/C++):运行时不可以修改变量的类型
# 动态类型(python):运行时可以修改变量的类型
# myint = 10
# myint = 'hehe'
# print myint

# myint = 10
# myfloat = 3.14
# # 内建(buildin)函数
# print type(myint)
# print type(myfloat)

# 精度问题
# myint = 1000000000000000
# myint *= myint
# print type(myint)
# print myint

# 字符串
# mystr = 'a'
# print type(mystr)
# 双引号可以包含在单引号之中打印(不需要转义字符)
# 双引号可包含在单引号中输出
# 多种引号可以包含在三引号中输出
# print 'my name is "jin"'
# print "my name is 'jin'"
# print '''my name is 'jin' "hahaha"'''

# 字符串基本操作
# 使用索引的方式获取某个字符串
# mystr = 'abcd'
# print mystr[0]
# print mystr[1]
# print mystr[2]
# print mystr[3]
# print '-'*20
# print mystr[100] 下标越界
# print mystr[-1] # 从后往前数第1个
# print mystr[-2] # 从后往前数第2个
# print mystr[-3] # 从后往前数第3个
# print mystr[-4] # 从后往前数第4个
 
# 取一段子字符串(切片)
# mystr = 'abcd'
# print mystr[1:3]
# print mystr[1:-1]
# print mystr[:-1]
# print mystr[3:]
# 只读到当前字符串长度就不往下读了
# print mystr[:100]
# 空区间即空字符串
# print mystr[2:1]

# # 字符串的拼接
# mystr1 = "hello"
# mystr2 = "world"
# result = mystr1 + mystr2
# print result
# # 字符串的重复
# mystr = '-'
# mystr *= 20
# print mystr

# 求字符串的长度
# mystr = "hello"
# print len(mystr)

# 格式化字符串
# format = 'a = %d'
# a = 100
# result = format % a
# print result

# 格式化的操作是字符串内置的,和print没有任何关系
# a = 100
# print 'a = %d' % a

# 布尔类型
# a = True
# b = False
# print a,b
# print type(a),type(b)

# 输入/输出(返回值是字符串)
# mystr = raw_input('> ')
# int() 也相当于一个内建函数,将其他类型转化为int型
# print 2 * int(mystr)

# Python 不会隐式的把字符串转换为数字或者把数字转化为字符串
# 强类型
# print 100 + mystr

# 运算符
# 大部分算数运算符和关系运算符规则和c语言一样
# Python中的除法有三种风格

# 1.传统除法(同C语言)
# a = 1
# b = 2
# print a / b

# 2.地板(floor)除法 - 向下取整
# a = -1
# b = 2
# print a // b

# 3.精确除法
# from __future__ import division # 导入一个标准库里的包
# a = 1
# b = 2
# print a / b

# 乘方操作
# a = 2
# b = 3
# print a ** b

# print 2 < 3 < 4 # 等价于 2 < 3 and 3 < 4(推荐)

# 列表/元祖/字典 Python内置的基本数据类型

# 1.列表 - 可以理解为C语言的数组
# a = [1,2,3,4]
# print a
# print a[0],a[-1]
# print a[1:3] # 取出来为子列表
# a[0] = 'haha'
# print a
# print type(a)

# 可以混合类型
# b = [1,'hello',2.0,"world"]
# print b

# 列表嵌套(n维数组)

# 2.元祖(tuple) - 元祖的操作都和列表相同,但是不能对某个元素进行修改
# a = (1,2,3,4)
# a[0] = 'aaa'

# 3.字典(哈希表) - 可以存储键值对
# a = {'ip':'127.0.0.1','port':8080}
# print a['ip']

# 引用 - 将变量名理解为一个标签,创建一个变量的时候,就是在对应编号上贴一个标签
# a = 100
# print id(a), id(100) # 表示唯一一个对象的编号
# a = 200
# print id(a), id(200)
# b = a
# print id(a), id(b), id(200)

# 缩进
# a = 1
# b = 1
# if a > b:
#     print 'a > b'
#     print '>>>>>'
# elif a < b:
#     print 'a < b'
#     print '<<<<<'
# else:
#     print 'a = b'
#     print '====='

# 循环
# 1.while
# count = 0
# while count < 3:
#     print '-' * (count+1)
#     count += 1

# 2.for
# mystr = 'abcd'
# for item in mystr:
#     print item

# for - 元祖
# for item in [1,2,3,4]:
#     print item

# for - 字典
# a = {'ip':'127.0.0.1','port':8080}
# for key in a:
#     print key,a[key]

# for - range
# for i in range(1,101): # range的返回值就是一个列表,前闭后开
#     print i
# 
# for i in range(1,101,2): # 第三位为步长
#     print i

# break : 找出 1~100 中第一个3的倍数
# for i in range(1,101):
#     if i % 3 == 0:
#         break
# print i

# continue : 找出 1~100 中所有3的倍数
# for i in range(1,100):
#     if i % 3 != 0:
#         continue
#     print i

# pass语句(空语句)
# for i in range(1,100):
#     if i % 2 == 0:
#         pass
#     else:
#         print i

# 列表解析
# 获取都 1~100 序列的平方序列
# 期望的结果 [1,4,9,16,25...]
# print [x ** 2 for x in range(1,101)]

# 获取所有奇数的平方
# print [x ** 2 for x in range(1,101,2)]

# 获取所有3的倍数的平方
# print [x ** 2 for x in range(1,101) if x % 3 == 0]

# 函数定义
# def Add(x, y):
#     return x + y
# 
# ret = Add(1,2) # 必须是两个可以相加的变量
# print ret
# ret = Add('hello','world')
# print ret

# C++重载
# 函数名相同,函数签名不同
# 签名: 参数列表 & c-v限定符(const-volatile)

# Python重载
# 后面的同名函数会覆盖前面的函数
# def Add(x,y):
#     return x + y
# def Add(x,y,z):
#     return x + y + z

# 缺省参数
# def Add(x,y,z=0):
#     return x + y + z
# 
# print Add(10,20)
# print Add(10,20,30)

# 一次返回多个值
# def GetPoint():
#     x = 10
#     y = 20
#     return x, y
# 
# a,b = GetPoint()
# print a,b

# def Top():
#     value = 10
#     ret = True
#     return ret, value
# # unpack
# ret,_ = Top() # 顺序只和返回值有关
# _,value = Top()
# print ret
# print value

# function 类型
# 函数其实就是一个变量,类型为function
# def Add(x, y):
#     return x + y
# print type(Add)
# # 并且可赋值
# fun = Add
# print fun(1,2)
# # 函数 - 就是一个可调用对象
# 
# print dir(Add)

# 文件操作
# r w a rt(以文本方式读) rb(以二进制方式读)
# f = open('./test.txt','w') # 返回一个文件对象,其中包含文件描述符
# f.write('aaa\n')
# f.write('bbb\n')
# f.write('ccc\n')
# f.close()

# f = open('./test.txt','r')
# for line in f:
#     print line, # 加逗号是防止了print打印自身的 \n
# f.close()

# 综合例子
# 统计文件中单词出现的频率
# 文件有若干行,每行是一个单词
# data = {}
# f = open('./test.txt','r')
# for line in f:
#     if line in data: # 判断in前面的东西是否在in后面可以查找得到
#         data[line] += 1
#     else:
#         data[line] = 1
# f.close()
# print data

# 模块
# 创建一个add.py文件(同一目录下)
# 导入add
# import add
# print add.Add(1,2)
# from [文件名] improt [函数名]
# from add import Add
# print Add(1,2)

import sys
sys.path.append('/')
print sys.path
