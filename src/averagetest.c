#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/averagedepth.h"
#include "../inc/datareader.h"

int main(void){
	probabilities* array = getproba("data/access_count2.txt");
	/* probabilities* array = getproba("benchmarks/benchmark2.in"); */
	printf("Average depth: %lf\n",getavg(array));
	free(array->proba);
	free(array->proba_sums);
	free(array);
	return EXIT_SUCCESS;
}
