#!/usr/bin/python3.5
# -*-coding:Utf-8 -*
from Node import *

class AverageDepthCalculator(object):

    def __init__(self, proba):
        self.call_count = 0
        self.avg_depth = -1
        self.proba = proba
        self.root = None
        self.call_average = [[None] * (len(proba)+1)] * len(proba)

    def average_depth(self):
        self.avg_depth = self.average_depth_rec(0, len(self.proba), 1);
        print(self.call_average[0][len(self.proba)-1])
        self.root = Node(0)

    def average_depth_rec(self, i_low, i_high, depth):
        self.call_count += 1

        diff = i_high - i_low
        if diff == 1:
            return self.proba[i_low]*depth
        if diff == 0:
            return 0
        if diff < 0:
            raise ValueError("BASTARD")
        
        # If we already did the operation we return it
        # if self.call_average[i_low][i_high] != None:
            # return self.call_average[i_low][i_high]

        low = self.average_depth_rec(i_low, i_low, depth+1)
        high = self.average_depth_rec(i_low+1, i_high, depth+1)
        min_index = i_low
        min_val = self.proba[i_low]*depth + low + high
        
        for i in range(i_low+1, i_high):
            low = self.average_depth_rec(i_low, i, depth+1)
            high = self.average_depth_rec(i+1, i_high, depth+1)
            val = self.proba[i]*depth + low + high
            if val < min_val:
                min_val = val
                min_index = i

        self.call_average[i_low][i_high] = min_val
        return min_val
