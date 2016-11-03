#!/usr/bin/python3.5
# -*-coding:Utf-8 -*
from Node import *

class AverageDepthCalculator(object):

    def __init__(self):
        self.call_count = 0
        self.avg_depth = -1
        self.root = None
        self.proba = None

    def average_depth(self, proba):
        self.proba = proba
        self.root, self.avg_depth = self.average_depth_rec(0, len(proba), 1);

    def average_depth_rec(self, i_low, i_high, depth):
        self.call_count += 1
        diff = i_high - i_low
        if diff == 1:
            return Node(i_low), self.proba[i_low]*depth
        if diff == 0:
            return None, 0
        if diff < 0:
            raise ValueError("BASTARD")

        best_node_low, low = self.average_depth_rec(i_low, i_low, depth+1)
        best_node_high, high = self.average_depth_rec(i_low+1, i_high, depth+1)
        min_index = i_low
        min_val = self.proba[i_low]*depth + low + high
        
        for i in range(i_low+1, i_high):
            node_low, low = self.average_depth_rec(i_low, i, depth+1) 
            node_high, high = self.average_depth_rec(i+1, i_high, depth+1)
            val = self.proba[i]*depth + low + high
            if val < min_val:
                min_val = val
                min_index = i
                best_node_low = node_low
                best_node_high = node_high

        node = Node(min_index)
        node.add_child(LEFT, best_node_low)
        node.add_child(RIGHT, best_node_high)
        return node, min_val
