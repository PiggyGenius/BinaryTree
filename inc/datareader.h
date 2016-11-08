#ifndef DATAREADER_H
#define DATAREADER_H
#include "tree.h"

typedef struct {
	double* proba;
	double* proba_sums;
	uint32_t length;
} probabilities;

probabilities* getproba(char* filename);

void disparray(double* proba,uint32_t length);

void treetoarray(Tree* tree,uint32_t length);

void printtree(uint32_t length);

void nodetoarray(Node* root);

#endif
