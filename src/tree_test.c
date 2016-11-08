#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

int main(void) {
	Node* root = init(0, 0.3);
	add_son(root, 1, 0.2, 0);
	add_son(root->left_son, 3, 0.1, 0);
	add_son(root->left_son, 4, 0.1, 1);
	add_son(root, 2, 0.2, 1);
	add_son(root->right_son, 6, 0.4, 1);
	print_tree(root);
	free_tree(root);
}

