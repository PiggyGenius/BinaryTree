#!/usr/bin/python3.5
# -*-coding:Utf-8 -*

from Node import *

def average_depth(values, proba):

    def average_depth_rec(i_low, i_high, depth):
        
        diff = i_high - i_low
        if diff == 1:
            return Node(i_low), proba[i_low]*depth
        if diff == 0:
            return None, 0
        if diff < 0:
            raise ValueError("BASTARD")

        best_node_low, low = average_depth_rec(i_low, i_low, depth+1)
        best_node_high, high = average_depth_rec(i_low+1, i_high, depth+1)
        min_index = i_low
        min_val = proba[0]*depth + low + high
        
        for i in range(i_low+1, i_high):
            node_low, low = average_depth_rec(i_low, i, depth+1) 
            node_high, high = average_depth_rec(i+1, i_high, depth+1)
            val = proba[i]*depth + low + high
            if val < min_val:
                min_val = val
                min_index = i
                best_node_low = node_low
                best_node_high = node_high

        node = Node(min_index)
        node.add_child(LEFT, best_node_low)
        node.add_child(RIGHT, best_node_high)

        return node, min_val


    return average_depth_rec(0, len(values), 1);


if __name__ == "__main__":

    values = [1,2,3,4,5,6,7,8]
    proba = [0.1,0.2,0.2,0.1,0.1,0.1,0.1,0.1]
    v = [1,2,3]
    p1 = [0.2,0.4,0.4]
    p2 = [0.5,0.3,0.2]
    p3 = [0.6,0.2,0.2]
    p4 = [0.3,0.2,0.5]
    p5 = [0.1,0.3,0.6]

    for t in [p1, p2, p3, p4, p5]:
        tree, val = average_depth(v, t)
        print(tree.str(len(v)))
        print("Bonus : average_depth = ", val, "\n")
