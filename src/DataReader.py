#!/usr/bin/python3.5
# -*-coding:Utf-8 -*

class DataReader(object):

    def __init__(self):
        self.data_array = []
        self.access_array = []
        self.access_count = 0

    # If we merge read and process, we don't have to store data_array !
    def read_file(self,filename):
        data_file = open(filename,'r')
        i = 0;
        for line in data_file:
            self.data_array.append(int(line))
            self.access_count += int(line)
            i += 1

    def process_array(self):
        for access_value in self.data_array:
            self.access_array.append(access_value / self.access_count)
        return self.access_array

    def get_access_array(self):
        return self.access_array
