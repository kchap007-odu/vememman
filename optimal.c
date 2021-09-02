#include "optimal.h"

/**
 * Constructor for Optimal replacement structure.
 *
 * @param fc the frame count, or number of frames to use for the algorithm
 * @param r pointer to the array containing the memory requests
 * @param tr the number of requests contained in array r
 *
 * @return pointer to the Optimal replacement structure
 */
optimal_t *optimal_constructor(int fc, int *r, int tr)
{
    optimal_t *o = malloc(sizeof(optimal_t));
    o->frames = intArray_constructor(fc);
    o->statistics = statistics_constructor(fc);
    o->nextUse = intArray_constructor(fc);
    o->requestPosition = 0;
    o->pendingRequests = r;
    o->totalRequests = tr;
    o->itemsInBuffer = 0;
}

/**
 * Destructor for Optimal replacement structure.
 *
 * @param o the Optimal replacement structure to free
 */
void optimal_destructor(optimal_t *o)
{
    intArray_destructor(o->frames);
    intArray_destructor(o->nextUse);
    statistics_destructor(o->statistics);
    free(o);
}

/**
 * Runs the Optimal replacement algorithm.
 *
 * @param o the Optimal replacement structure
 */
void optimal_run(optimal_t *o)
{
    for (int i = 0; i < o->totalRequests; i++)
    {
        o->pendingRequests[o->requestPosition];
        optimal_findNextUse(o);
        optimal_addToBuffer(o, o->pendingRequests[i]);
        o->requestPosition++;
    }
}

/**
 * Checks whether the target value is already in the buffer,
 * if so, it increments the hit count. If not, it increments the
 * miss count and decides which value to replace in accordance
 * with Optimal replacement method.
 *
 * @param o the Optimal replacement structure
 * @param v the value to add
 */
void optimal_addToBuffer(optimal_t *o, int v)
{
    if (valueInArray(v, o->frames, o->statistics->frameCount))
        o->statistics->hitCount++;
    else
    {
        if (o->itemsInBuffer == o->statistics->frameCount)
            o->frames[optimal_determineValueToReplace(*o)] = v;
        else
            o->frames[o->itemsInBuffer++] = v;
        o->statistics->missCount++;
    }
}

/**
 * Calculates the number of requests until the frames will be used again.
 *
 * @param o the Optimal replacement structure.
 */
void optimal_findNextUse(optimal_t *o)
{
    for (int i = 0; i < o->statistics->frameCount; i++)
        o->nextUse[i] = __INT16_MAX__;

    for (int i = 0; i < o->itemsInBuffer; i++)
        for (int j = o->requestPosition; j < o->totalRequests; j++)
            if (o->frames[i] == o->pendingRequests[j])
                o->nextUse[i] = j - o->requestPosition;
}

/**
 * Determines which value to replace by looking for the
 * frame with the farthest distance until it is called again.
 *
 * @param o the Optimal replacement structure
 */
int optimal_determineValueToReplace(optimal_t o)
{
    int mv = 0, p = 0;
    for (int i = 0; i < o.itemsInBuffer; i++)
    {
        mv = max(mv, o.nextUse[i]);
        if (mv == o.nextUse[i])
            p = i;
    }

    return p;
}

/**
 * Prints the current state of the Optimal replacement structure.
 *
 * @param o the structure to print
 */
void optimal_debugPrint(const optimal_t o)
{
    printf("Optimal\n");
    printf("  Buffer: [");
    for (int i = 0; i < o.statistics->frameCount; i++)
        printf("%d ", o.frames[i]);
    printf("]\n");

    printf("  Next use: [");
    for (int i = 0; i < o.statistics->frameCount; i++)
        printf("%d ", o.nextUse[i]);
    printf("]\n");

    printf("  **Hits : %d  Misses: %d**\n", o.statistics->hitCount, o.statistics->missCount);
}

/**
 * Prints the formatted statistics of the Optimal replacement run.
 *
 * @param o the Optimal replacement structure
 * @param ps the page size used on the run
 */
void optimal_printStatistics(const optimal_t o, int ps)
{
    double fp = statistics_calculateFaultRate(*(o.statistics));
    printf("%9d    %10d    %9s   %16.2f%%\n", ps, o.statistics->frameCount, "Optimal", fp);
}