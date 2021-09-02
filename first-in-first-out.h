#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "statistics.h"
#include "helpers.h"

typedef struct fifo_t
{
    int pointerPosition;
    int *frames;
    statistics_t *statistics;
} fifo_t;

fifo_t *fifo_constructor(int);
void fifo_destructor(fifo_t *);

void fifo_addToBuffer(fifo_t *, int);
void fifo_incrementPointer(fifo_t *);

void fifo_debugPrint(const fifo_t);
void fifo_printStatistics(const fifo_t, int);

#endif