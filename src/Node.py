#! /usr/bin/env python3.5
# -*- coding: utf-8 -*-

LEFT, RIGHT = 0, 1

class Node:
    def __init__(self, value, proba):
        self.value = value
        self.proba = proba
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

