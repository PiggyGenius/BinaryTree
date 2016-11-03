#!/usr/bin/python3.5
# -*-coding:Utf-8 -*
import sys
sys.path.insert(0,"src/")
from Node import *
from algorithm import *
from DataReader import DataReader
from GraphicalTree import GraphicalTree


# We read the data file and print data as C array
dr = DataReader()
dr.read_file("data/access_count.txt")
dr.process_array()

tree, val = average_depth(range(len(dr.access_array)),dr.access_array)

graph_tree = GraphicalTree()
print(tree.str_tree())
graph_tree.create_tree(tree.str_tree())
graph_tree.write_tree()
