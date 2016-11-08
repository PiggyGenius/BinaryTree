#ifndef AVERAGEDEPTH_H
#define AVERAGEDEPTH_H

#include "datareader.h"
#include "tree.h"

typedef struct tree_info {
	int root_index;
	double avg_depth;
} tree_info;

double proba_sum(uint32_t low_index,uint32_t high_index);

double avg_comp(uint32_t low_index,uint32_t high_index);

double getavg(probabilities* array);

#endif
