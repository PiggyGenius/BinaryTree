#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/datareader.h"
#include "../inc/tree.h"
#include "../inc/list.h"

uint32_t** tree_array;

probabilities* getproba(char* filename){
	FILE* data;
	uint32_t size;
	double value;
	double total_value = 0;
	probabilities* array = NULL;
	List* values_list = NULL;
	
	data = fopen(filename,"r");
	if(data == NULL){
		fprintf(stderr,"The file doesn't exist or couldn't be opened.\n");
		exit(EXIT_FAILURE);
	}

	/* We need to check scanf for a mysterious reason ? */
	values_list = init_list();
	for(size=0;!feof(data);size++){
		if(fscanf(data,"%lf",&value) != -1){
			add_element(values_list,value);
			total_value += value;
		}
	}
	fclose(data);
	array = getlistproba(values_list,total_value);
	free_list(values_list);
	return array;
}

void treetoarray(Tree* tree,uint32_t length){
	tree_array = malloc(length*sizeof(uint32_t*));
	for(uint32_t i=0;i<length;i++)
		tree_array[i] = malloc(2*sizeof(uint32_t));
	nodetoarray(tree->root);
	for(uint32_t i=0;i<length;i++)
		free(tree_array[i]);
	free(tree_array);
	printtree(length);
}

void printtree(uint32_t length){
	printf("{\n");
	for(uint32_t i=0;i<length-1;i++)
		printf("{%u, %u},\n",tree_array[i][0],tree_array[i][1]);
	printf("{%u, %u} };\n",tree_array[length][0],tree_array[length][1]);
}

void nodetoarray(Node* root){
	if(root->left_son == NULL)
		tree_array[root->value][0] = -1;
	else {
		tree_array[root->value][0] = root->left_son->value;
		nodetoarray(root->left_son);
	}
	if(root->left_son == NULL)
		tree_array[root->value][1] = -1;
	else {
		tree_array[root->value][1] = root->right_son->value;
		nodetoarray(root->right_son);
	}
}

void disparray(double* proba,uint32_t length){
	for(uint32_t i=0;i<length;i++)
		printf("%lf\n",proba[i]);
}
