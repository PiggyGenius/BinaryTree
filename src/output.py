#! /usr/bin/env python3.5
# -*- coding: utf-8 -*-

from Node import *

def printBSTroot(n):
    print("static int BSTroot = " + str(n) + ";")

def printNodes(node):
    if node == None:
        return ''
    s = printNodes(node.children[LEFT])
    s += repr(node)
    s += printNodes(node.children[RIGHT])
    return s

def printBSTtree(node, n):
    s = "static int BSTtree[" + str(n) + "][2] = { "
    s += printNodes(node)
    s += " };"
    return s
    

if __name__ == "__main__":
    print(printBSTroot(1))
    a = Node(1, 0.2)
    a.add_child(LEFT, Node(0, 0.5))
    a.add_child(RIGHT, Node(2, 0.3))
    print(printBSTtree(a, 3))
    
