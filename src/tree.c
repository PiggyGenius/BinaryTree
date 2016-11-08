#include "../inc/tree.h"

Node* init_tree(int value, float proba)
{
	Node* n = malloc(sizeof(Node));
	n->value = value;
	n->proba = proba;
	n->left_son = NULL;
	n->right_son = NULL;
	return n;
}

void add_son(Node* n, int value, float proba, int side)
{
	if (n == NULL) {
		fprintf(stderr, "Error : null pointer\n");
		exit(EXIT_FAILURE);
	}
	if (side == 0) {
		if (n->left_son != NULL) {
			fprintf(stderr, "Error : this node already has a left son\n");
			exit(EXIT_FAILURE);
		}
		n->left_son = init_tree(value, proba);	
	} else {
		if (n->right_son != NULL) {
			fprintf(stderr, "Error : this node already has a right son\n");
			exit(EXIT_FAILURE);
		}
		n->right_son = init_tree(value, proba);
	}
}

void free_tree(Node* n) {
	if (n == NULL) {
		fprintf(stderr, "Error : null pointer\n");
		exit(EXIT_FAILURE);
	}
	if (n->left_son != NULL) {
		free_tree(n->left_son);
	}
	if (n->right_son != NULL) {
		free_tree(n->right_son);
	}
	free(n);
}

void print_tree_rec(Node* n, int tabs) {
	if (n == NULL) {
		return;
	}
	print_tree_rec(n->left_son, tabs+1);
	for (int i = 0; i < tabs; i++) {
		printf("  ");
	}
	printf("%d\n", n->value);
	print_tree_rec(n->right_son, tabs+1);
}

void print_tree(Node* n) {
	if (n == NULL) {
		fprintf(stderr, "Error : null pointer\n");
		exit(EXIT_FAILURE);
	}
	print_tree_rec(n, 0);
}
