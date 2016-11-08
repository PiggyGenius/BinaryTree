#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/list.h"

List* init_list(void)
{
	List* l = malloc(sizeof(List));	
	l->size = 0;
	l->first = NULL;
	return l;
}

void add_element(List* l, double value)
{
	if (l == NULL) {
		fprintf(stderr, "Null pointer.");
		exit(EXIT_FAILURE);
	}
	Element* elt = malloc(sizeof(Element));
	elt->value = value;
	elt->next = NULL;
	if (l->size == 0){
		l->first = elt;
		l->last = l->first;
	}
	else {
		l->last->next = elt;
		l->last = elt;
	}
	l->size += 1;
}

probabilities* getlistproba(List* l,double total_value){
	Element* elem = l->first;
	probabilities* array = malloc(sizeof(probabilities));
	array->length = l->size;
	array->proba = malloc(array->length*sizeof(double));
	array->proba_sums = malloc((array->length+1)*sizeof(double));

	array->proba_sums[0] = 0;
	for(uint32_t i=0;i<array->length;i++){
		array->proba[i] = elem->value / total_value;
		array->proba_sums[i+1] = array->proba_sums[i] + array->proba[i];
		elem = elem->next;
	}
	return array;
}

void print_list(List* l)
{
	Element* elt = l->first;
	while (elt != NULL) {
		printf("%lf ", elt->value);
		elt = elt->next;
	}
	printf("\nSize = %d\n", l->size);
}

void free_list(List *l)
{
	Element* elt = l->first;
	Element* tmp;
	while (elt != NULL) {
		tmp = elt->next;
		free(elt);
		elt = tmp;
	}
	free(l);
}
