#! /usr/bin/env python3.5
# -*- coding: utf-8 -*-

from Node import *

def strBSTroot(root):
    return "static int BSTroot = " + str(root) + ";\n" 

def strBSTtree(node, n):
    s = "static int BSTtree[" + str(n) + "][2] = { "
    s += strNodes(node)
    s = s[:-2] + " };"
    return s

def strNodes(node):
    s = ''
    # left son
    if node.children[LEFT] != None:
        s += strNodes(node.children[LEFT]) + ", "
    # node
    s += repr(node)
    # right son
    if node.children[RIGHT] != None:
        s += ", " + strNodes(node.children[RIGHT]) + ", " 
    return s

def strAll(node, n):
    return strBSTroot(node.value) + strBSTtree(node, n);
    

if __name__ == "__main__":
    a = Node(1, 0.2)
    a.add_child(LEFT, Node(0, 0.5))
    a.add_child(RIGHT, Node(2, 0.3))
    print(strAll(a, 3))
    
