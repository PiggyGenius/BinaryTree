#!/usr/bin/python3.5
# -*-coding:Utf-8 -*
import sys
sys.path.insert(0,"src/")
from GraphicalTree import GraphicalTree

tree = GraphicalTree()
tree.create_tree("{ {-1,-1}, {0,2 }, {-1 ,-1}}")
print(tree.tree_string())
tree.write_tree()
