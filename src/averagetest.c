#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/averagedepth.h"
#include "../inc/datareader.h"

int main(void){
	probabilities* array = getproba("../data/access_count.txt");
	printf("Average depth: %lf.\n",getavg(array->proba,array->length));
	return EXIT_SUCCESS;
}
