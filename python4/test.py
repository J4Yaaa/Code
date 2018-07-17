#!/usr/bin/env python
# coding=utf-8

###############################################
# 模块
###############################################

# 导入的包会默认在sys.path中查找
# import sys
# print sys.path

#import 顺序
# Python 标准库
# 第三方库
# 自定制模块

# import as 语句
# import os.path as op
# print op.exists('test.py')

# from import 语句
# from add import Add

# 导入模块意味着被执行
# 导入模块的两个步骤
# 1.
# 2.

# 只打印一次hello world
# import add
# import add

# import 和 reload
# (热加载: 不终止进程,让修改生效)代码执行过程中,模块的内容可能会被改变,reload可以不终止程序,重新导入模块

# 打印两次hello world
# import add
# reload(add) # reload是函数

# print globals() # 查看 __name__,如果__name__等于__main__,那么他就是入口函数
# import add
# add.Print()

# 模块 对应的是 文件
# 包 对应的是 目录

# print type(calc) # 包本质上也是一个模块,只是程序员区分包和模块
# print calc

# import calc.add # 必须将里面的模块也导入,才可以使用这个模块
# calc.add

#######################################
# 面向对象(OOP)
#######################################

# 抽象: 抓住重点关注的主体,忽略一些不需要关注的细节

# 面向对象: 类的组合(更推荐使用),一个大的概念(学校类)里面包含了很多小的概念(老师类,学生类,教学楼类...)

# 封装: 降低学习成本和出错概率
#       将不需要给调用者调用的结构隐藏起来

# 组合/包含: 多个小的类组合成一个大的类,来解决一个相对复杂的问题
#            组合表示 **has-a** 语义(A 包含 B)
#            公有继承表示 **is-a** 语义(A 是 B)

# 继承
# 公有继承表示 **is-a** 语义(A 是 B)
# 如 土猫 是 猫

# 多态: 本质就是运行是可以自动识别对象的类型
#       可以简化代码

# 自省/反射: 只对象在运行时(程序运行过程中)可以识别自己的信息
#            dir,id,type,__doc__,__name__ 这些内置属性和方法就是自省的体现

# C++ 中的类型萃取也可以起到相似的作用,但是是在编译过程中执行的
# C++ typeid也可以实现,但是功能不完善,不推荐使用,降低了效率

# 函数/类/拉姆达表达式 - 改变作用域

# 创建一个类
class Test(object): # 不继承其他类可以在括号里写object
    """
    定义一个Test类
    """
    pass

# help(Test)

# 定义一个对象
t = Test() # 省略掉 new 这个关键字
print id(t)
print type(t)
