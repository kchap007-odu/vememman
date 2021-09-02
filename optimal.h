#ifndef OPTIMAL_H_INCLUDED
#define OPTIMAL_H_INCLUDED

#include <stdio.h>

#include "helpers.h"
#include "statistics.h"

typedef struct optimal_t
{
    int *frames;
    int *nextUse;
    int *pendingRequests;
    int itemsInBuffer;
    int requestPosition;
    int totalRequests;
    statistics_t *statistics;
} optimal_t;

optimal_t *optimal_constructor(int, int *, int);
void optimal_destructor(optimal_t *);

void optimal_run(optimal_t *);

void optimal_addToBuffer(optimal_t *, int);
void optimal_findNextUse(optimal_t *);
int optimal_determineValueToReplace(optimal_t);

void optimal_debugPrint(const optimal_t);
void optimal_printStatistics(const optimal_t, int);

#endif