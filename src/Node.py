#! /usr/bin/env python3.5
# -*- coding: utf-8 -*-

LEFT, RIGHT = 0, 1

class Node:
    def __init__(self, value):
        self.value = value
        self.children = [None, None]

    def add_child(self, pos, node):
        if self.children[pos] != None:
            raise ValueError("This node already has a child here.")
        self.children[pos] = node

    def __repr__(self):
        s = "{"
        if self.children[LEFT] == None:
            s += "-1"
        else:
            s += str(self.children[LEFT].value)
        s += "; "
        if self.children[RIGHT] == None:
            s += "-1"
        else:
            s += str(self.children[RIGHT].value)
        s += "}"
        return s


    def str_tree(self):
        return "{ " + self.turn_to_str() + " };"


    def turn_to_str(self):
        s = ''
        # left son
        if self.children[LEFT] != None:
            s += self.children[LEFT].turn_to_str() + ", "
        # node
        s += repr(self)
        # right son
        if self.children[RIGHT] != None:
            s += ", " + self.children[RIGHT].turn_to_str()
        return s
    
    def value(self):
        return self.value

    def str(self, n):
        return "static int BSTroot = " + str(self.value) + ";\n" + self.str_tree(n);
     
