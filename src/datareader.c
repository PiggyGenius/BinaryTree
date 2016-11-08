#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/datareader.h"

probabilities* getproba(char* filename){
	FILE* data;
	uint32_t size;
	double* values = NULL;
	double total_value = 0;
	data = fopen(filename,"r");
	if(data == NULL){
		fprintf(stderr,"The file doesn't exist or couldn't be opened.\n");
		exit(EXIT_FAILURE);
	}

	for(size=0;!feof(data);size++){
		values = realloc(values,(size+1)*sizeof(double));
		fscanf(data,"%lf",values+size);
		total_value += values[size];
	}
	fclose(data);

	probabilities* array = malloc(sizeof(probabilities));
	array->length = size-1;
	array->proba = malloc(array->length*sizeof(double));
	array->proba_sums = malloc((array->length+1)*sizeof(double));

	array->proba_sums[0] = 0;
	for(uint32_t i=0;i<array->length;i++){
		array->proba[i] = values[i] / total_value;
		array->proba_sums[i+1] = array->proba_sums[i] + array->proba[i];
	}
	free(values);
	return array;
}

void disparray(double* proba,uint32_t length){
	for(uint32_t i=0;i<length;i++)
		printf("%lf\n",proba[i]);
}
