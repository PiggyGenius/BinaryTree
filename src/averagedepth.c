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


double avg_comp(uint32_t low_index, uint32_t high_index){
	total_call_count += 1;
	if (low_index == high_index) {
		return 0;
	} else if (low_index + 1 == high_index) {
		depth_array[low_index][high_index-1].avg_depth = 1;
		depth_array[low_index][high_index-1].root_index = low_index;
	/* We have to check if value is very close to 0, can't compare floats to 0.0 */
	} else if (fabs(depth_array[low_index][high_index-1].avg_depth) <= 10e-7) {
		unique_call_count += 1;
		double lower, higher, total;
		double min_result, new_result;
		int min_index;

		total = proba_sum(low_index,high_index);
		lower = 0.0;
		higher = avg_comp(low_index+1,high_index) * (proba_sums[high_index]-proba_sums[low_index+1]) / total;
		min_result = 1 + lower + higher;
		min_index = low_index;

		for(uint32_t i=low_index+1;i<high_index;i++){
			lower = avg_comp(low_index,i) * (proba_sums[i]-proba_sums[low_index]) / total;
			higher = avg_comp(i+1,high_index) * (proba_sums[high_index]-proba_sums[i+1]) / total;
			new_result = 1 + lower + higher;

			if (min_result > new_result) {
				min_result = new_result;
				min_index = i;
			}
		}

		depth_array[low_index][high_index-1].avg_depth = min_result;
		depth_array[low_index][high_index-1].root_index = min_index;
		/* printf("[%d][%d] filled\n", low_index, high_index); */
	}
	return depth_array[low_index][high_index-1].avg_depth;
}


Node* build_nodes(int min_index, int max_index)
{
	/*  fonction recursive / plan :
	 *  chercher index i mis en root pour cet arbre dans depth_array 
	 *  lui mettre en fils gauche : min_index à i
	 *  lui mettre en fils droit : i+1 à max_index
	 *  Condition d'arret : si min = max, NULL */

	if (min_index == max_index) {
		return NULL;
	}

	if (min_index > max_index) {
		fprintf(stderr, "This should never happen\n");
		exit(EXIT_FAILURE);
	}

	int root_index = depth_array[min_index][max_index-1].root_index;
	/* printf("Min = %d, Max = %d, root = %d\n", min_index, max_index, root_index); */
	Node* n = malloc(sizeof(Node));
	n->value = root_index;
	n->proba = proba[root_index];
	n->left_son = build_nodes(min_index, root_index);
	n->right_son = build_nodes(root_index+1, max_index);
	return n;
}


Tree* build_tree(int min_index, int max_index, double min_depth)
{
	Tree* t = malloc(sizeof(Tree));
	t->root = build_nodes(min_index, max_index);
	t->avg_depth = min_depth;
	return t;
}


Tree* getavg(probabilities* array)
{
	double min_depth;
	total_call_count = 0;
	unique_call_count = 0;

	proba = array->proba;
	proba_sums = array->proba_sums;
	depth_array = malloc(array->length*sizeof(tree_info*));
	for(uint32_t i=0; i < array->length; i++)
		depth_array[i] = calloc(array->length,sizeof(tree_info));

	/* avg_comp returns the optimal average number of comparisons
	 * the average depth is the avg comp minus 1 */
	min_depth = avg_comp(0, array->length) - 1.0;
	Tree* tree = build_tree(0, array->length, min_depth);
	/* print_tree(tree); */

	for(uint32_t i=1; i < array->length; i++)
		free(depth_array[i]);
	free(depth_array);

	/* printf("Total call count: %u\n",total_call_count); */
	/* printf("Unique call count: %u\n",unique_call_count); */
	return tree;
}

