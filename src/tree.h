#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
	int value;
	float proba;
	struct Node *left_son;
	struct Node *right_son;
} Node;

// create a node
Node* init(int value, float proba);

// add a son to the node
// if side == 0, left_son
// else, right son
void add_son(Node* n, int value, float proba, int side);

// free the tree
void free_tree(Node* n);

// print the tree
void print_tree(Node* n);
