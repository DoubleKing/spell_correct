#!/usr/bin/python
# -*- coding: UTF-8 -*-
# 文件名：client.py

import socket               # 导入 socket 模块

s = socket.socket(socket.AF_INET,)        # 创建 socket 对象
s.connect(('23.105.203.121', 8887))
while 1:
    word = raw_input('please enter query world: ')
    s.send(word)
    print s.recv(1024)
s.close()