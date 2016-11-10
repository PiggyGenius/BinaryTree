#ifndef AVERAGEDEPTH_H
#define AVERAGEDEPTH_H

#include "data_io.h"
#include "tree.h"

typedef struct tree_info {
	int root_index;
	double avg_comp;
} tree_info;


Tree* getavg(probabilities* array);

#endif
