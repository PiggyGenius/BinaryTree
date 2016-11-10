#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include "../inc/averagedepth.h"


double* proba = NULL;
double* proba_sums = NULL;
tree_info** comp_array = NULL;
uint32_t total_call_count;
uint32_t unique_call_count;

/* returns the sum of the probabilities between
 * low_index (included) and high_index (excluded) */
double proba_sum(uint32_t low_index,uint32_t high_index){
	return proba_sums[high_index] - proba_sums[low_index];
}


/* returns the average number of comparisons in the tree made with the
 * elements between low_index (included) and high_index (excluded) */
double avg_comp(uint32_t low_index, uint32_t high_index){
	total_call_count += 1;
	if (low_index == high_index) {
		return 0;
	} else if (low_index + 1 == high_index) {
		comp_array[low_index][high_index-1].avg_comp = 1;
		comp_array[low_index][high_index-1].root_index = low_index;
		/* We have to check if value is very close to 0, can't compare floats to 0.0 */
	} else if (fabs(comp_array[low_index][high_index-1].avg_comp) <= 10e-7) {
		unique_call_count += 1;
		double lower, higher, total;
		double min_result, new_result;
		int min_index;

		total = proba_sum(low_index,high_index);
		lower = 0.0;
		higher = avg_comp(low_index+1,high_index) * proba_sum(low_index+1, high_index) / total;
		min_result = 1 + lower + higher;
		min_index = low_index;

		for(uint32_t i=low_index+1;i<high_index;i++){
			lower = avg_comp(low_index,i) * proba_sum(low_index, i) / total;
			higher = avg_comp(i+1,high_index) * proba_sum(i+1, high_index) / total;
			new_result = 1 + lower + higher;

			if (min_result > new_result) {
				min_result = new_result;
				min_index = i;
			}
		}

		comp_array[low_index][high_index-1].avg_comp = min_result;
		comp_array[low_index][high_index-1].root_index = min_index;
	}
	return comp_array[low_index][high_index-1].avg_comp;
}


double sum(int i, int j){
	double s = 0;
	for (int k = i; k <=j; k++)
		s += proba[k];
	return s;
}

double avg_comp3(uint32_t low_index,int32_t n){
	/*double cost[n][n];*/
	printf("%u\n",low_index);
	for (int i = 0; i < n; i++) {
		comp_array[i][i].avg_comp = proba[i];
		comp_array[i][i].root_index = i;
	}

	for (int L=2; L<=n; L++) {
		for (int i=0; i< n-L+1; i++) {
			int j = i+L-1;
			comp_array[i][j].avg_comp = (double) INT_MAX;
			for (int r=comp_array[i][j-1].root_index; r<=comp_array[i+1][j].root_index; r++) {
				double c = ((r > i)? comp_array[i][r-1].avg_comp:0) + 
					((r < j)? comp_array[r+1][j].avg_comp:0) + proba_sum(i, j);
				if (c < comp_array[i][j].avg_comp) {
					comp_array[i][j].avg_comp = c;
					comp_array[i][j].root_index = r;
				}
			}
		}
	}
	return comp_array[0][n-1].avg_comp;
}

/* once the depth array has been filled, build the nodes of the tree */
Node* build_nodes(int min_index, int max_index)
{
	if (min_index > max_index) {
		return NULL;
	}

	/*if (min_index > max_index) {*/
		/*fprintf(stderr, "This should never happen\n");*/
		/*exit(EXIT_FAILURE);*/
	/*}*/

	int root_index = comp_array[min_index][max_index].root_index;
	Node* n = malloc(sizeof(Node));
	n->value = root_index;
	n->proba = proba[root_index];
	n->left_son = build_nodes(min_index, root_index-1);
	n->right_son = build_nodes(root_index+1, max_index);
	return n;
}


/* once the depth array has been filled, build the tree
 * (call build_nodes for that) and return it */
Tree* build_tree(int min_index, int max_index, double min_depth)
{
	Tree* t = malloc(sizeof(Tree));
	t->root = build_nodes(min_index, max_index-1);
	/*for (int i = 0; i < max_index; i++) {*/
		/*for (int j = 0; j < max_index; j++) {*/
			/*printf("%d ", comp_array[i][j].root_index);*/
		/*}*/
		/*printf("\n");*/
	/*}*/
					
	t->avg_depth = min_depth;
	return t;
}


/* main function, returns the tree (which contains the average depth */
Tree* getavg(probabilities* array)
{
	double min_depth;
	total_call_count = 0;
	unique_call_count = 0;

	proba = array->proba;
	proba_sums = array->proba_sums;
	comp_array = malloc(array->length*sizeof(tree_info*));
	for(uint32_t i=0; i < array->length; i++)
		comp_array[i] = calloc(array->length,sizeof(tree_info));

	/* avg_comp returns the optimal average number of comparisons
	 * the average depth is the avg_comp minus 1 */
	min_depth = avg_comp3(0, array->length) - 1.0;
	printf("%lf\n",min_depth+1);
	Tree* tree = build_tree(0, array->length, min_depth);

	for(uint32_t i=0; i < array->length; i++)
		free(comp_array[i]);
	free(comp_array);

	return tree;
}

