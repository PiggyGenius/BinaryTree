#ifndef DATAREADER_H
#define DATAREADER_H

#include <stdlib.h>
#include <stdint.h>
#include "tree.h"

typedef struct {
	double* proba;
	double* proba_sums;
	uint32_t length;
} probabilities;

probabilities* getproba(FILE*,uint32_t length);

void treetoarray(Tree* tree,uint32_t length);

void free_array(probabilities* array);

#endif
