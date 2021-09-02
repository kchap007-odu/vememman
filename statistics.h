#ifndef STATISTICS_H_INCLUDED
#define STATISTICS_H_INCLUDED

#include <stdlib.h>

typedef struct statistics_t
{
    int frameCount;
    int missCount;
    int hitCount;
} statistics_t;

statistics_t *statistics_constructor(int);
void statistics_destructor(statistics_t *);
double statistics_calculateFaultRate(const statistics_t);

#endif