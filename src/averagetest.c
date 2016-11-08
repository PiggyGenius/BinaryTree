#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/averagedepth.h"
#include "../inc/datareader.h"

int main(void){
	probabilities* array = getproba("data/access_count2.txt");
	printf("Average depth: %lf\n",getavg(array));
	free(array->proba);
	free(array->proba_sums);
	free(array);
	return EXIT_SUCCESS;
}
