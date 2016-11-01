#! /usr/bin/env python3.5
# -*- coding: utf-8 -*-

from Node import *

def strBSTroot(n):
    return "static int BSTroot = " + str(n) + ";"

def strBSTtree(node, n):
    s = "static int BSTtree[" + str(n) + "][2] = { "
    s += repr(node)
    s += " };"
    return s
    

if __name__ == "__main__":
    print(strBSTroot(1))
    a = Node(1, 0.2)
    a.add_child(LEFT, Node(0, 0.5))
    a.add_child(RIGHT, Node(2, 0.3))
    print(strBSTtree(a, 3))
    
