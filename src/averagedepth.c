#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/averagedepth.h"


double* proba = NULL;

double proba_sum(uint32_t low_index,uint32_t high_index){
	double sum = 0;
	for(uint32_t i=low_index;i<high_index;i++)
		sum += proba[i];
	return sum;
}

double avgdepth(uint32_t low_index,uint32_t high_index){
	if(high_index-low_index <= 1)
		return high_index-low_index;

	double lower, higher, total;
	double min_result, new_result;
	total = proba_sum(low_index,high_index);
	lower = avgdepth(low_index,low_index) * proba_sum(low_index,low_index) / total;
	higher = avgdepth(low_index+1,high_index) * proba_sum(low_index+1,high_index) / total;

	min_result = 1 + lower + higher;
	for(uint32_t i=low_index+1;i<high_index;i++){
		lower = avgdepth(low_index,i) * proba_sum(low_index,i) / total;
		higher = avgdepth(i+1,high_index) * proba_sum(i+1,high_index) / total;
		new_result = 1 + lower + higher;
		if(min_result > new_result)
			min_result = new_result;
	}
	return min_result;
}

double getavg(double* proba_array,uint32_t length){
	proba = proba_array;
	return avgdepth(0,length);
}
