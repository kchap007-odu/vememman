#ifndef RU_H_INCLUDED
#define RU_H_INCLUDED

#include <stdio.h>
#include <string.h>

#include "statistics.h"
#include "helpers.h"

typedef struct ru_t
{
    int *frames;
    int *lastUsed;
    int itemsInBuffer;
    int leastRecent;
    statistics_t *statistics;
} ru_t;

ru_t *ru_constructor(int, int);
void ru_destructor(ru_t *);

void ru_addToBuffer(ru_t *, int);
int ru_determineValueToReplace(const ru_t);
void ru_resetCounter(ru_t *, int);
void ru_incrementCounters(ru_t *);

void ru_debugPrint(const ru_t);
void ru_printStatistics(const ru_t, int);

#endif