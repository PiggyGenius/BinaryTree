#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "../inc/averagedepth.h"


double* proba = NULL;
double* proba_sums = NULL;
tree_info** depth_array = NULL;
uint32_t total_call_count;
uint32_t unique_call_count;

double proba_sum(uint32_t low_index,uint32_t high_index){
	double sum = 0;
	for(uint32_t i=low_index;i<high_index;i++)
		sum += proba[i];
	return sum;
}

double avgdepth(uint32_t low_index, uint32_t high_index)
{
	total_call_count += 1;
	if(high_index-low_index <= 1)
		return high_index-low_index;

	/* We have to check if value is very close to 0, can't compare floats to 0.0 */
	if(fabs(depth_array[low_index][high_index-1].avg_depth) > 10e-7)
		return depth_array[low_index][high_index-1].avg_depth;

	unique_call_count += 1;
	double lower, higher, total;
	double min_result, new_result;
	int min_index;

	total = proba_sum(low_index,high_index);
	lower = 0.0;
	higher = avgdepth(low_index+1,high_index) * (proba_sums[high_index]-proba_sums[low_index+1]) / total;
	min_result = 1 + lower + higher;
	min_index = 0;

	for(uint32_t i=low_index+1;i<high_index;i++){
		lower = avgdepth(low_index,i) * (proba_sums[i]-proba_sums[low_index]) / total;
		higher = avgdepth(i+1,high_index) * (proba_sums[high_index]-proba_sums[i+1]) / total;
		new_result = 1 + lower + higher;
		if (min_result > new_result) {
			min_result = new_result;
			min_index = i;
		}
	}

	depth_array[low_index][high_index-1].avg_depth = min_result;
	depth_array[low_index][high_index-1].root_index = min_index;
	return min_result;
}

double getavg(probabilities* array)
{
	double min_depth;
	total_call_count = 0;
	unique_call_count = 0;

	proba = array->proba;
	proba_sums = array->proba_sums;
	depth_array = malloc(array->length*sizeof(tree_info*));
	for(uint32_t i=0; i < array->length; i++)
		depth_array[i] = calloc(array->length,sizeof(tree_info));

	min_depth = avgdepth(0, array->length);

	for(uint32_t i=1; i < array->length; i++)
		free(depth_array[i]);
	free(depth_array);

	printf("Total call count: %u\n",total_call_count);
	printf("Unique call count: %u\n",unique_call_count);
	return min_depth;
}
