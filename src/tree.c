#include "../inc/tree.h"

Tree* init_tree(void)
{
	Tree* t = malloc(sizeof(Tree));
	t->root = NULL;
	t->avg_depth = 0;
	return t;
}


void free_nodes(Node* n)
{
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


void free_tree(Tree *t)
{
	free_nodes(t->root);
	free(t);
}


void print_nodes_rec(Node* n, int tabs)
{
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


void print_tree(Tree* t)
{
	if (t == NULL) {
		fprintf(stderr, "Error : null pointer\n");
		exit(EXIT_FAILURE);
	}
	print_nodes_rec(t->root, 0);
}
