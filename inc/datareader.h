#ifndef DATAREADER_H
#define DATAREADER_H

typedef struct {
	double* proba;
	double* proba_sums;
	uint32_t length;
} probabilities;

probabilities* getproba(char* filename);

void disparray(double* proba,uint32_t length);


#endif
