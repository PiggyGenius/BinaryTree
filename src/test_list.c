#include <stdlib.h>
#include <stdio.h>
#include "../inc/list.h"

int main(void) {
	List* l = init();
	add_element(l, 2);
	add_element(l, 3);
	add_element(l, 6);
	add_element(l, 11);
	print_list(l);
	free_list(l);
}
