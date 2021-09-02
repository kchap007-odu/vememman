#include "first-in-first-out.h"

/**
 * Constructor for First In, First Out replacement.
 *
 * @param fc the frame count, or number of frames to use for the algorithm
 *
 * @return pointer to a First In, First Out structure
 */
fifo_t *fifo_constructor(int fc)
{
    fifo_t *f = malloc(sizeof(fifo_t));
    f->statistics = statistics_constructor(fc);
    f->frames = intArray_constructor(fc);
    f->pointerPosition = 0;

    return f;
}

/**
 * Destructor for First In, First Out structure.
 *
 * @param f the FIFO structure to free
 */
void fifo_destructor(fifo_t *f)
{
    free(f->statistics);
    free(f->frames);
    free(f);
}

/**
 * Checks whether the target value is already in the buffer,
 * if so, it increments the hit count. If not, it increments the
 * miss count and decides which value to replace in accordance
 * with FIFO method.
 *
 * @param f the FIFO structure
 * @param v the value to add
 */
void fifo_addToBuffer(fifo_t *f, int v)
{
    if (!valueInArray(v, f->frames, f->statistics->frameCount))
    {
        f->frames[f->pointerPosition] = v;
        fifo_incrementPointer(f);
        f->statistics->missCount++;
    }
    else
        f->statistics->hitCount++;
}

/**
 * Increments the pointer used in the FIFO circular buffer.
 *
 * @param f the FIFO structure to modify
 */
void fifo_incrementPointer(fifo_t *f)
{
    f->pointerPosition = (f->pointerPosition + 1) % f->statistics->frameCount;
}

/**
 * Prints the current state of the FIFO structure.
 *
 * @param f the FIFO structure to print
 */
void fifo_debugPrint(const fifo_t f)
{
    printf("First In, First Out\n");
    printf("  Buffer: [");
    for (int i = 0; i < f.statistics->frameCount; i++)
        printf("%d ", f.frames[i]);
    printf("]\n");
    printf("  **Hits : %d  Misses: %d**\n", f.statistics->hitCount, f.statistics->missCount);
}

/**
 * Prints the formatted statstics of the FIFO run.
 *
 * @param f the FIFO structure
 * @param ps the page size used
 */
void fifo_printStatistics(const fifo_t f, int ps)
{
    double fp = statistics_calculateFaultRate(*(f.statistics));
    printf("%9d    %10d    %9s   %16.2f%%\n", ps, f.statistics->frameCount, "FIFO", fp);
}