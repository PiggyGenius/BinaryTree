#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/datareader.h"
#include "../inc/list.h"

probabilities* getproba(char* filename){
	FILE* data;
	uint32_t size;
	double value;
	double total_value = 0;
	probabilities* array = NULL;
	List* values_list = NULL;
	
	data = fopen(filename,"r");
	if(data == NULL){
		fprintf(stderr,"The file doesn't exist or couldn't be opened.\n");
		exit(EXIT_FAILURE);
	}

	/* We need to check scanf for a mysterious reason ? */
	values_list = init_list();
	for(size=0;!feof(data);size++){
		if(fscanf(data,"%lf",&value) != -1){
			add_element(values_list,value);
			total_value += value;
		}
	}
	fclose(data);
	array = getlistproba(values_list,total_value);
	free_list(values_list);
	return array;
}

void disparray(double* proba,uint32_t length){
	for(uint32_t i=0;i<length;i++)
		printf("%lf\n",proba[i]);
}
