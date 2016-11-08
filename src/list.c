#include "list.h"

List* init(void)
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
	elt->next = l->first;
	l->first = elt;
	l->size ++;
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
