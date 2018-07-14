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

# 内建函数
# len()
# a = [1,2,3]
# print len(a)
# b = 'hehe'
# print len(b)
# c = ('a','b')
# print len(c)

# max/min
# a = [1,2,3]
# print max(a),min(a)
# b = 'abc'
# print max(b),min(b)
# c = {'a','b','c'}
# print max(c),min(c)

# sorted
# 并不修改以前的序列,而是返回一个新的序列
# a = [5,4,6,3,9]
# print sorted(a)
# print sorted(a,reverse=True)

# sum()
# 要求序列中的元素都是数字
# a = [1,2,3,4]
# print sum(a)

# enumerate
# 找出元素在列表中的下标
# def Find(input_list,x):
#     # i 是列表下标,item 是值
#     for i , item in enumerate(input_list):
#         if item == x:
#             return i
#     else:
#         return None
# 
# a = [1,2,3,4]
# Find(a,2)

# zip
# 传入的列表长度最好相同,如果不相同可能会丢失元素
# a = [1,2,3]
# b = [4,5,6]
# c = [7,8,9]
# print zip(a,b,c)

#################################################
# 字符串
#################################################

# 引号
# '''/""" 可以跨多行

# 字符串不可变
# a = 'hehe'
# # a[0] = 'a' #错误
# # 可以这样修改
# b = 'a' + a[1:]
# print b

# 只适用于字符串

# % 格式化输出
# 这里格式化以后是生成了新的字符串
# x = 100
# print 'x = %d' % x

# 原始字符串
# # 在原始字符串中,转义字符不生效
# print 'hello \n world'
# # 在字符串前面加 r
# print r'hello \n world'

# repr 函数
# 和str的区别 : repr输出的字符串是一个合法的python语句,是给python看的
#               str输出的字符串是给程序员看的
# a = 'hello'
# print str(a)
# print repr(a)

# 反引号操作符 -- 和repr用法一致   
# 即将被废用
# a = 'hello'
# print `a`

# 常用函数
# 字符串合并
# a = ['aa','bb','cc']
# print ','.join(a)

# 字符串切分,返回结果为列表
# a = 'aa bb cc'
# print a.split(' ')

# 判定字符串的开头和结尾是不是某个指定的字符串
# a = 'hello world'
# print a.startswith('he')
# print a.endswith('ld')

# strip 去掉字符串前后的空白字符
# a = '   hello    '
# print '[%s]' % a.strip()
# print '[%s]' % a

# 让字符串左对齐/右对齐/居中
# a = 'hello world'
# print '[%s]' % a.ljust(30)
# print '[%s]' % a.rjust(30)
# print '[%s]' % a.center(30)

# 字符串查找子串
# 返回为查询字符串的起始位置的下
# a = 'hello world'
# print a.find('wor')

# 字符串替换
# a = 'hello world'
# print a.replace('hello','hahaha')

# 判定字符串是一个字母还是数字
# a = 'helloworld'
# print a.isdigit()
# print a.isalpha()
# b = '1234'
# print b.isdigit()
# print b.isalnum()
# print b.isalpha()

# 字符串中大小写转换
# a = 'Hello World'
# print a.upper()
# print a.lower()

#####################################
# 列表
#####################################

# 删除
# a = [1,2,3]
# del a[0]
# del(a[0])
# print a

# a = [1,2,3]
# a.remove(1)
# print a

# 列表的比较操作
# a = [4,2,3]
# b = [1,5,6]
# print a == b
# print a > b # 从第0个元素开始比较大小,如果第一个相同,就比价下一个
# print a < b
# # 元素类型不同也可以比较
# a = ['hello',1]
# b = [1,'hello']
# print a > b

# 链接操作,extend,并没有创建新的列表对象,而是直接尾插
# a = [1,2,3]
# b = [4,5,6]
# a.extend(b)
# print a

# 列表内建函数

# pop 
# 默认是尾删
# a.pop(0) 头删

# append

# list.sort 不创建新的链表,直接在原列表上修改
# a = [5,4,6,3,9]
# list.sort(a)
# print a
# list.sort(a,reverse=True)
# print a

# 列表的深拷贝和浅拷贝
# a = [100,[1,2]]
# b = a
# c = list(a)
# d = a[:]
# print id(a),id(b),id(c),id(d) # 此处只能判定b是浅拷贝,c,d不确定
# print id(a[0]),id(a[1])
# print id(c[0]),id(c[1]) # 可判断是浅拷贝
# print id(d[0]),id(d[1]) # 可判断是浅拷贝,因为内部对象的id相同  

# 不太懂
# a[0] = 0
# print a[0],b[0],c[0],d[0]

# 可以使用 copy 进行深拷贝
# Python中的copy.deepcopy 并不是把所有对象进行深拷贝
# 在这里,100本身就不需要深拷贝,他是不可变对象,在内存中保存一份即可,大家都可以去访问
# 这些不可变对象,在整个内存中有且只有一个
# 整数/元组/字符串 - 都是不可变
# 列表是可变对象,所以这里进行了深拷贝
# import copy
# a = [100,[1,2]]
# b = copy.deepcopy(a)
# print id(a),id(b)
# print id(a[0]),id(a[1])
# print id(c[0]),id(c[1])

#####################################
# 元组
#####################################
# 元祖中元素id不可变!!!元祖中元素id不可变!!!
# 元祖不支持extend,sort,append操作

# 元祖不可变指的是元祖中包含的若干个元素的id不可变
# 以下的例子,修改了列表中的元素,但是列表的id没变
# a = ([1,2,3],[4,5,6])
# a[0][0] = 100
# print a
