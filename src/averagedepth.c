#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>
#include "../inc/averagedepth.h"

/*############################## Useful variables and functions ##############################*/

double* proba = NULL;
double* proba_sums = NULL;
tree_info** comp_array = NULL;
uint32_t total_call_count;
uint32_t unique_call_count;

/* returns the sum of the probabilities between
 * low_index and high_index (both included) */
static double proba_sum(uint32_t low_index,uint32_t high_index){
	return proba_sums[high_index+1] - proba_sums[low_index];
}

/*############################## Average comparisons functions ###############################*/

/* RECURSIVE VERSION, DEPRECATED (see iterative version below, muuuuuuch faster)
 * returns the average number of comparisons in the tree made with the
 * elements between low_index (included) and high_index (excluded) */

/* static double avg_comp_rec(uint32_t low_index, uint32_t high_index){ */
/* 	total_call_count += 1; */
/* 	if (low_index == high_index) { */
/* 		return 0; */
/* 	} else if (low_index + 1 == high_index) { */
/* 		comp_array[low_index][high_index-1].avg_comp = 1; */
/* 		comp_array[low_index][high_index-1].root_index = low_index; */
/* 		#<{(| We have to check if value is very close to 0, can't compare floats to 0.0 |)}># */
/* 	} else if (fabs(comp_array[low_index][high_index-1].avg_comp) <= 10e-7) { */
/* 		unique_call_count += 1; */
/* 		double lower, higher, total; */
/* 		double min_result, new_result; */
/* 		int min_index; */
/*  */
/* 		total = proba_sum(low_index,high_index-1); */
/* 		lower = 0.0; */
/* 		higher = avg_comp_rec(low_index+1,high_index) * proba_sum(low_index+1, high_index-1) / total; */
/* 		min_result = 1 + lower + higher; */
/* 		min_index = low_index; */
/*  */
/* 		for(uint32_t i=low_index+1;i<high_index;i++){ */
/* 			lower = avg_comp_rec(low_index,i) * proba_sum(low_index, i-1) / total; */
/* 			higher = avg_comp_rec(i+1,high_index) * proba_sum(i+1, high_index-1) / total; */
/* 			new_result = 1 + lower + higher; */
/*  */
/* 			if (min_result > new_result) { */
/* 				min_result = new_result; */
/* 				min_index = i; */
/* 			} */
/* 		} */
/*  */
/* 		comp_array[low_index][high_index-1].avg_comp = min_result; */
/* 		comp_array[low_index][high_index-1].root_index = min_index; */
/* 	} */
/* 	return comp_array[low_index][high_index-1].avg_comp; */
/* } */


/* ITERATIVE VERSION, faster */
/* returns the average number of comparisons in the tree made with
 * all the nodes (indexes between 0 and size-1) */
static double avg_comp_iter(int32_t size)
{
	/* filling of the first diagonal of the memoization tabular */
	for (int i = 0; i < size; i++) {
		comp_array[i][i].avg_comp = proba[i];
		comp_array[i][i].root_index = i;
	}

	/* iteration through the upper diagonals of comp_array */
	for (int length = 2; length <= size; length++) {
		/* for each row i */
		for (int i=0; i < size - length + 1; i++) {
			/* column j */
			int j = i + length - 1;
			comp_array[i][j].avg_comp = (double)INT_MAX;
			/* we iterate through the possible roots and keep the smallest cost */
			for (int root = comp_array[i][j-1].root_index; root <= comp_array[i+1][j].root_index; root++) {
				double cost = ((root > i)? comp_array[i][root-1].avg_comp:0) + ((root < j)? comp_array[root+1][j].avg_comp:0) + proba_sum(i, j);
				/* if the cost is lower (better), we update the minimal cost and the chosen root */
				if (cost < comp_array[i][j].avg_comp) {
					comp_array[i][j].avg_comp = cost;
					comp_array[i][j].root_index = root;
				}
			}
		}
	}

	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			printf("%u ",comp_array[i][j].root_index);
		}
		printf("\n");
	}

	return comp_array[0][size-1].avg_comp;
}


/*################################# Tree building functions ##################################*/

/* once the depth array has been filled, build the nodes of the tree */
static Node* build_nodes(int min_index, int max_index)
{
	if (min_index > max_index) {
		return NULL;
	}
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
static Tree* build_tree(int min_index, int max_index, double min_depth)
{
	Tree* t = malloc(sizeof(Tree));
	t->root = build_nodes(min_index, max_index-1);
	t->avg_depth = min_depth;
	return t;
}


/*###################################### Main function #######################################*/

/* returns the tree (which contains the average depth */
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
	min_depth = avg_comp_iter(array->length) - 1;
	/* printf("%lf\n",min_depth); */
	Tree* tree = build_tree(0, array->length, min_depth);

	for(uint32_t i=0; i < array->length; i++)
		free(comp_array[i]);
	free(comp_array);

	return tree;
}

