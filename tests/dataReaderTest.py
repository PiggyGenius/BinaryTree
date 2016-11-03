#!/usr/bin/python3.5
# -*-coding:Utf-8 -*
import sys
sys.path.insert(0,"src/")
from DataReader import DataReader

dr = DataReader()
dr.read_file("data/access_count.txt")
dr.process_array()
print(dr.access_string())
