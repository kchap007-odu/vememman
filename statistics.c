#include "statistics.h"

/**
 * Constructs an structure to track the statistics associated with
 * running a paging algorithm.
 *
 * @param fc the number of frames to allocate to the statistics calculation
 */
statistics_t *statistics_constructor(int fc)
{
    statistics_t *s = malloc(sizeof(statistics_t));
    s->frameCount = fc;
    s->hitCount = 0;
    s->missCount = 0;

    return s;
}

/**
 * Destructor for a statistics object.
 *
 * @param s the statistics structure to destroy
 */
void statistics_destructor(statistics_t *s)
{
    free(s);
}

/**
 * Calculates the page fault rate contained in a statistics structure.
 *
 * @param s the statistics structure
 *
 * @return the percentage, from 0 to 100, of page faults in the run.
 */
double statistics_calculateFaultRate(const statistics_t s)
{
    return (double)s.missCount / (double)(s.hitCount + s.missCount) * 100;
}