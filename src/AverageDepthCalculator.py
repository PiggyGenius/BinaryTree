#!/usr/bin/python3.5
# -*-coding:Utf-8 -*
from Node import *

class AverageDepthCalculator(object):
    
    def __init__(self, proba):
        self.call_count = 0
        self.avg_depth = -1
        self.proba = proba
        self.proba_calc = [[None] * (len(proba)+1)] * (len(proba)+1)
        self.comp_array = [[None for i in range(len(proba)+1)] for j in range(len(proba))]
        self.comp_array2 = [[None for i in range(len(proba)+1)] for j in range(len(proba))]
        self.root = None

    def average_depth(self):
        print("Average with memoisation: ",self.average_calc(0,len(self.proba)))
        print("Call count: ",self.call_count)
        self.call_count = 0

        print("Average no memoisation: ",self.average_calc_nomem(0,len(self.proba)))
        print("Call count: ",self.call_count)
        self.call_count = 0

        print("Simple average depth: ",self.simple_average(range(len(self.proba)),self.proba))
        print("Call count: ",self.call_count)
        self.call_count = 0

        print("Old average depth: ",self.old_average(0, len(self.proba), 1))
        print("Call count: ",self.call_count)
        self.call_count = 0

        # print("With memoisation comp_array: ",self.comp_array,'\n')
        # print("No memoisation comp_array: ",self.comp_array2)

    def average_calc(self,low_index,high_index):
        #print("Entering function: ",low_index,high_index)
        self.call_count += 1
        if high_index - low_index <= 1:
            return high_index - low_index

        if self.comp_array[low_index][high_index] == None:
            #print("Entering memoisation: ",low_index,high_index)
            total = sum(self.proba[low_index:high_index])
            lower = self.average_calc(low_index,low_index) * sum(self.proba[low_index:low_index]) / total
            higher = self.average_calc(low_index+1,high_index) * sum(self.proba[low_index+1:high_index]) / total

            min_result = 1 + lower + higher
            for i in range(low_index+1, high_index):
                lower = self.average_calc(low_index, i) * sum(self.proba[low_index:i]) / total
                higher = self.average_calc(i+1, high_index) * sum(self.proba[i+1:high_index]) / total
                new_result = 1 + lower + higher
                if min_result > new_result:
                    min_result = new_result
            self.comp_array[low_index][high_index] = min_result
            # print(low_index,high_index,": ",min_result)
        return self.comp_array[low_index][high_index]

    def simple_average(self,values,proba):
        self.call_count += 1
        l = len(values)
        if l in [0,1]:
            return l
        results = [0]*l
        for i in range(l):
            low = self.simple_average(values[0:i],proba[0:i])*sum(proba[0:i])/sum(proba)
            high = self.simple_average(values[i+1:l],proba[i+1:l])*sum(proba[i+1:l])/sum(proba)
            results[i] = 1 + low + high
        return min(results)


    def old_average(self, i_low, i_high, depth):
        self.call_count += 1

        diff = i_high - i_low
        if diff == 1:
            return self.proba[i_low]*depth
        if diff == 0:
            return 0
        if diff < 0:
            raise ValueError("BASTARD")
        
        low = self.old_average(i_low, i_low, depth+1)
        high = self.old_average(i_low+1, i_high, depth+1)
        min_index = i_low
        min_val = self.proba[i_low]*depth + low + high
        
        for i in range(i_low+1, i_high):
            low = self.old_average(i_low, i, depth+1)
            high = self.old_average(i+1, i_high, depth+1)
            val = self.proba[i]*depth + low + high
            if val < min_val:
                min_val = val
                min_index = i
        self.comp_array2[i_low][i_high] = min_val
        return min_val

    def average_calc_nomem(self,low_index,high_index):
        self.call_count += 1
        if low_index == high_index - 1:
            return 1
        if low_index == high_index:
            return 0
        lower = self.average_calc_nomem(low_index,low_index) * sum(self.proba[low_index:low_index]) / sum(self.proba[low_index:high_index])
        higher = self.average_calc_nomem(low_index+1,high_index) * sum(self.proba[low_index+1:high_index]) / sum(self.proba[low_index:high_index])
        min_result = 1 + lower + higher
        for i in range(low_index+1,high_index):
            lower = self.average_calc_nomem(low_index, i) * sum(self.proba[low_index:i])/sum(self.proba[low_index:high_index])
            higher = self.average_calc_nomem(i+1,high_index) * sum(self.proba[i+1:high_index])/sum(self.proba[low_index:high_index])
            new_result = 1 + lower + higher
            if min_result > new_result:
                min_result = new_result
        self.comp_array2[low_index][high_index] = min_result
        return min_result
