#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../inc/data_io.h"
#include "../inc/tree.h"
/* #include "../inc/list.h" */

int32_t** tree_array;

/* fill a probabilities structure with the given value array */
static probabilities* getprobaarray(double* value_array,uint32_t length,double total_value){
	probabilities* array = malloc(sizeof(probabilities));
	array->length = length;
	array->proba = malloc(array->length*sizeof(double));
	array->proba_sums = malloc((array->length+1)*sizeof(double));

	array->proba_sums[0] = 0;
	for(uint32_t i=0;i<array->length;i++){
		array->proba[i] = value_array[i] / total_value;
		array->proba_sums[i+1] = array->proba_sums[i] + array->proba[i];
	}
	return array;
}


/* parse the given file and call getprobaarray */
probabilities* getproba(FILE* data, uint32_t length){
	double value;
	double total_value = 0;
	double value_array[length];
	
	if(data == NULL){
		fprintf(stderr,"The file doesn't exist or couldn't be opened.\n");
		exit(EXIT_FAILURE);
	}

	for(uint32_t i=0;!feof(data);i++){
		if(fscanf(data,"%lf",&value) != -1){
			value_array[i] = value;
			total_value += value;
		}
	}
	return getprobaarray(value_array,length,total_value);
}


/* print the list of nodes according to the tree_array filled by nodetoarray */
static void printtree(int32_t length){
	if(length == 0){
		printf("{}");
		return;
	}
	for(int32_t i=0;i<length-1;i++)
		printf("{%d, %d}, \n",tree_array[i][0],tree_array[i][1]);
	printf("{%d, %d}",tree_array[length-1][0],tree_array[length-1][1]);
}


/* fill a tree_array with the given tree */
static void nodetoarray(Node* root){
	if(root->left_son == NULL)
		tree_array[root->value][0] = -1;
	else {
		tree_array[root->value][0] = root->left_son->value;
		nodetoarray(root->left_son);
	}
	if(root->right_son == NULL)
		tree_array[root->value][1] = -1;
	else {
		tree_array[root->value][1] = root->right_son->value;
		nodetoarray(root->right_son);
	}
}


/* print the required output with the given tree */
void treetoarray(Tree* tree, uint32_t length)
{
	tree_array = malloc(length*sizeof(int32_t*));
	for(uint32_t i=0;i<length;i++)
		tree_array[i] = malloc(2*sizeof(int32_t));

	printf("static int BSTroot = %d;\n", tree->root->value);
	printf("static int BSTtree[%d][2] = {\n", length);
	nodetoarray(tree->root);
	printtree(length);
	printf(" };\n");
	for(uint32_t i=0;i<length;i++)
		free(tree_array[i]);
	free(tree_array);
}


/* free the probabilities structure */
void free_array(probabilities* array)
{
	free(array->proba);
	free(array->proba_sums);
	free(array);
}
