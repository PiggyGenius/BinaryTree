#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/averagedepth.h"
#include "../inc/datareader.h"

int main(void){
	/* probabilities* array = getproba("data/access_count2.txt"); */
	probabilities* array = getproba("benchmarks/benchmark2.in");
	Tree* t = getavg(array);
	printf("Average depth: %lf\n", t->avg_depth);
	/*treetoarray(t,array->length);*/
	free(array->proba);
	free(array->proba_sums);
	free(array);
	free_tree(t);
	return EXIT_SUCCESS;
}
