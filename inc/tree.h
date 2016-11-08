#ifndef NODE_H
#define NODE_H

#include<stdlib.h>
#include<stdio.h>

typedef struct Node {
	int value;
	float proba;
	float avg_depth;
	struct Node *left_son;
	struct Node *right_son;
} Node;

typedef struct Tree {
	Node* root;
	float avg_depth;
} Tree;

// create a node
Tree* init_tree(void);

// add a son to the node
// if side == 0, left_son
// else, right son
// void add_son(Node* n, int value, float proba, int side);

// free the tree
void free_tree(Tree *t);

// print the tree
void print_tree(Tree* t);

#endif
