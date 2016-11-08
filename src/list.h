#include <stdlib.h>
#include <stdio.h>

typedef struct Element {
	double value;
	struct Element* next;
} Element;

typedef struct List {
	int size;
	struct Element* first;
} List;


List* init(void);

void add_element(List* l, double value);

void print_list(List* l);

void free_list(List *l);
