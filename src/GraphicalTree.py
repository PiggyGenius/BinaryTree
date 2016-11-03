#!/usr/bin/python3.5
# -*-coding:Utf-8 -*
import pygraphviz as pgv

class GraphicalTree(object):
    def __init__(self):
        self.tree = pgv.AGraph()

    def create_tree(self,tree_string):
        tree_string = tree_string.replace(' ','')
        tree_string = tree_string.replace('{','')
        tree_list = tree_string.split('},')
        tree_list[len(tree_list)-1] = tree_list[len(tree_list)-1].replace('}}','');
        for i in range(len(tree_list)):
            values = tree_list[i].split(',')
            for j in range(2):
                if values[j] != "-1":
                    self.tree.add_edge(i,values[j])

    def tree_string(self):
        return self.tree.string()

    def write_tree(self):
        self.tree.layout(prog='dot')
        self.tree.draw('visualization/tree.png')
