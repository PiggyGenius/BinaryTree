#!/usr/bin/python3.5
# -*-coding:Utf-8 -*

from DataReader import DataReader

dr = DataReader()
dr.read_file("data/access_count.txt")
dr.process_array()
print(dr.get_access_array())
