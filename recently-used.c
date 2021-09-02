#include "recently-used.h"

/**
 * Constructor for X Recently Used replacement algorithm.
 *
 * @param fc the frame count, or number of frames to use for the algorithm
 * @param d selector for Least or Most Recently Used style where a negative
 * number indicates LRU and a positive number indicates MRU.
 *
 * @return pointer fo the X Recently Used data structure.
 */
ru_t *ru_constructor(int fc, int d)
{
    ru_t *r = malloc(sizeof(ru_t));
    r->statistics = statistics_constructor(fc);
    r->frames = intArray_constructor(fc);
    r->lastUsed = intArray_constructor(fc);
    r->leastRecent = (d < 0);
    r->itemsInBuffer = 0;

    return r;
}

/**
 * Destructor for the X Recently Used structure.
 *
 * @param r the XRU structure to free
 */
void ru_destructor(ru_t *r)
{
    free(r->statistics);
    free(r->frames);
    free(r->lastUsed);
    free(r);
}

/**
 * Checks whether the target value is already in the buffer,
 * if so, it increments the hit count. If not, it increments the
 * miss count and decides which value to replace in accordance with
 * the X Recently Used method.
 *
 * @param r the XRU object
 * @param pn the page number to add
 */
void ru_addToBuffer(ru_t *r, int pn)
{
    if (valueInArray(pn, r->frames, r->statistics->frameCount))
    {
        ru_resetCounter(r, pn);
        r->statistics->hitCount++;
    }
    else
    {
        if (r->itemsInBuffer >= r->statistics->frameCount)
        {
            int tr = ru_determineValueToReplace(*r);
            r->frames[tr] = pn;
            r->lastUsed[tr] = 0;
        }
        else
        {
            r->frames[r->itemsInBuffer] = pn;
            r->lastUsed[r->itemsInBuffer] = 0;
            r->itemsInBuffer++;
        }
        r->statistics->missCount++;
    }
    ru_incrementCounters(r);
}

/**
 * Determines the value to replace in accordance with the LRU
 * or MRU methods.
 *
 * @param r the XRU structure
 *
 * @return the array position of the value to replace
 */
int ru_determineValueToReplace(const ru_t r)
{
    int mv = 0, p = 0;
    for (int i = 0; i < r.statistics->frameCount; i++)
    {
        mv = r.leastRecent ? max(mv, r.lastUsed[i]) : min(mv, r.lastUsed[i]);
        if (mv == r.lastUsed[i])
            p = i;
    }

    return p;
}

/**
 * Resets the referece counter for a specified value.
 *
 * @param r the XRU structure
 * @param v the value to reset the count for
 */
void ru_resetCounter(ru_t *r, int v)
{
    for (int i = 0; i < r->statistics->frameCount; i++)
        if (r->frames[i] == v)
            r->lastUsed[i] = 0;
}

/**
 * Increments the reference counter for each page in memory.
 *
 * @param r the XRU structure
 */
void ru_incrementCounters(ru_t *r)
{
    for (int i = 0; i < r->itemsInBuffer; i++)
        r->lastUsed[i]++;
}

/**
 * Prints the current state of the XRU structure.
 *
 * @param r the XRU structure
 */
void ru_debugPrint(const ru_t r)
{
    r.leastRecent ? printf("Least ") : printf("Most ");
    printf("Recently Used\n");
    printf("  Buffer: [");
    for (int i = 0; i < r.statistics->frameCount; i++)
        printf("%d ", r.frames[i]);
    printf("]\n");

    printf("  Last used: [");
    for (int i = 0; i < r.statistics->frameCount; i++)
        printf("%d ", r.lastUsed[i]);
    printf("]\n");

    printf("  **Hits : %d  Misses: %d**\n", r.statistics->hitCount, r.statistics->missCount);
}

/**
 * Prints the formatted statistics of the XRU run.
 *
 * @param r the XRU structure
 * @param ps the page size used
 */
void ru_printStatistics(const ru_t r, int ps)
{
    char a[4];
    double fp = statistics_calculateFaultRate(*(r.statistics));
    strcpy(a, r.leastRecent ? "LRU" : "MRU");
    printf("%9d    %10d    %9s   %16.2f%%\n", ps, r.statistics->frameCount, a, fp);
}