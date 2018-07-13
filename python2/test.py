#!/usr/bin/env python
# coding=utf-8

# a = 10
# print type(type(a))
# 
# print type(None)

# 比较两个对象的值

# 比较两个变量的身份
# a = 100
# b = a
# print id(a) == id(b)
# print a is b
# print a is not b

# 比较两个对象的类型
# a = 100
# print type(a) == type(100)
# 
# import types
# print type(a) == types.IntType # 效率比较高
# 
# # isinstance是一个内建函数
# print isinstance(a,int)

# 工厂模式 和 单例模式 都很重要!!!
# 工厂模式 - 写一组函数,每一个函数创建一个对应类型的对象
# 类型工厂函数

###########################################
# 数字和运算
###########################################

# 常用内置函数/模块
# abs
# print abs(10)
# print abs(-10)
# print abs(0)

# divmod 将除法和模运算结合在一起了
# a 是商, b 是余数
# a,b = divmod(10,3)
# print a,b

# round 对浮点数进程四舍五入
# import math
# print math.pi
# 
# for i in range(0,10):
#     print round(math.pi,i)

# oct(),hex() 将对应数字转换成字符串
# math/cmath 模块
# random模块,随机数模块,可以按照不同形式产生不同类别的随机数


###########################################
# 条件和循环
###########################################

# 条件表达式(有错!!!回去再看)
# a = 5
# b = 10
# ret = a if a < b else b
# print ret

# 和循环搭配的else
# 循环中途break是不会执行else的
# def Find(data_list,to_find):
#     for i in range(0,len(data_list)):
#         if data_list[i] == to_find:
#             return i
#     else: # 循环的补充,当循环条件不满足,就走else分支
#         return None

# 实现一个函数,打印出一个数的最大公约数
# def ShowMaxFactor(x):
#     count = x / 2
#     while count > 1:
#         if x % count == 0:
#             print 'lagest factor of %d is %d' % (x,count)
#             break
#         count -= 1
#     else:
#         print x,"is prime"
# 
# for i in range(10,20):
#     ShowMaxFactor(i)


###########################################
# 函数和可调用对象
###########################################

# 函数中也可以定义函数
# def Fun1():
#     def Fun2():
#         print 'hello'
#     Fun2()

# 闭包
# 一个对象中封装了函数指针个若干个参数
# 上面的Fun1就相当于一个函数闭包

# 函数的参数
# 形参不需要指定参数类型
# def Add(x,y):
#     return x + y
# 
# print Add(10,20)
# print Add('hello ','world')
# print Add([1,2,3],[4,5,6])
# print Add(10,'hehe') # 不可相加,错误!

# 默认参数
# def PrintPoint(x = 0,y = 0,z = 0):
#     print x,y,z
# 
# PrintPoint()
# PrintPoint(1)
# PrintPoint(1,2)
# PrintPoint(1,2,3)
# 
# # 关键字参数, C++ 中不可跳过左边的参数给右边赋值
# # python中可以,需要使用参数名指定
# PrintPoint(x=100,y=200)

# 关键字参数应用
# 内建函数 sorted
# 参数 : 可迭代的 -> 即可以用 for in 访问的
# cmp参数: 制定比较函数
# reverse参数: 指定升序降序
# key参数: 可以指定用什么比较

# a = [9,5,2,7]
# print sorted(a) # 默认升序
# print sorted(a,reverse=True) # reverse=True 降序排序


# 按绝对值排序
# a = [9,-5,2,7]
# def Cmp(x,y):
#     if abs(x) < abs(y):
#         return -1
#     elif abs(x) > abs(y):
#         return 1
#     else:
#         return 0
# print sorted(a,cmp=Cmp)

# 按字符串长度进行排序
# a = ['111','22222','3']
# print sorted(a,key=len)

# 参数组(变长参数),用列表方式进行操作
# join : 字符串的拼接
# split : 字符串分割

# def Log(prefix,*data):
#     print prefix + '\t'.join(data)
# 
# Log('[ERROR]','hello','world','hahaha')
# Log('[ERROR]','hello','world','xixixi')

# 日志分级
# 1.FATAL 致命级别
# 2.ERROR
# 3.WARNING
# 4.INFO
# 5.NOTICE
# 6.DEBUG

# **data : 表示字典
# def Log(prefix,**data):
#     # print prefix + data['ip'] + data['port'] 
#     print prefix + '\t'.join(data.values()) # values 将键值对中所有的值取出来放在列表里
# 
# Log('[ERROR]',ip='127.0.0.1',port='80')
# Log('[ERROR]',ip2='127.0.0.1',port2='80')

# 动态类型 + 参数组 -> 不需要函数重载

# 函数返回值
# def GetPoint():
#     return 1,2
# 
# print type(GetPoint()) # 返回值是一个元组

# 函数作为函数参数

# 函数作为函数返回值
# def Func1():
#     def Fun2():
#         print 'hehe'
#     return Fun2
# 
# f = Func1()
# f()

# 可调用对象
# 函数是可调用对象,可调用对象不一定是函数
# 只需要实现 __call__ 对应的函数即可
