#ifndef LIST_H
#define LIST_H
#include "datareader.h"

typedef struct Element {
	double value;
	struct Element* next;
} Element;

typedef struct List {
	int size;
	struct Element* first;
	struct Element* last;
} List;


List* init_list(void);

void add_element(List* l, double value);

void print_list(List* l);

void free_list(List *l);

probabilities* getlistproba(List* l,double total_value);

#endif
