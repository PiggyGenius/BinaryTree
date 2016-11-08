#include "../inc/tree.h"

Tree* init_tree(void)
{
	Tree* t = malloc(sizeof(Tree));
	t->root = NULL;
	t->avg_depth = 0;
	return t;
}

/* void add_son(Node* n, int value, float proba, int side) */
/* { */
/* 	if (n == NULL) { */
/* 		fprintf(stderr, "Error : null pointer\n"); */
/* 		exit(EXIT_FAILURE); */
/* 	} */
/* 	if (side == 0) { */
/* 		if (n->left_son != NULL) { */
/* 			fprintf(stderr, "Error : this node already has a left son\n"); */
/* 			exit(EXIT_FAILURE); */
/* 		} */
/* 		n->left_son = init_tree(value, proba);	 */
/* 	} else { */
/* 		if (n->right_son != NULL) { */
/* 			fprintf(stderr, "Error : this node already has a right son\n"); */
/* 			exit(EXIT_FAILURE); */
/* 		} */
/* 		n->right_son = init_tree(value, proba); */
/* 	} */
/* } */

void free_nodes(Node* n) {
	if (n == NULL) {
		fprintf(stderr, "Error : null pointer\n");
		exit(EXIT_FAILURE);
	}
	if (n->left_son != NULL) {
		free_nodes(n->left_son);
	}
	if (n->right_son != NULL) {
		free_nodes(n->right_son);
	}
	free(n);
}

void free_tree(Tree *t) {
	free_nodes(t->root);
	free(t);
}

void print_nodes_rec(Node* n, int tabs) {
	if (n == NULL) {
		return;
	}
	print_nodes_rec(n->left_son, tabs+1);
	for (int i = 0; i < tabs; i++) {
		printf("  ");
	}
	printf("%d\n", n->value);
	print_nodes_rec(n->right_son, tabs+1);
}

void print_tree(Tree* t) {
	if (t == NULL) {
		fprintf(stderr, "Error : null pointer\n");
		exit(EXIT_FAILURE);
	}
	print_nodes_rec(t->root, 0);
}
