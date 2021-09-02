#include <stdio.h>
#include <stdlib.h>

#include "first-in-first-out.h"
#include "recently-used.h"
#include "optimal.h"
#include "helpers.h"

int main(int argc, char **argv)
{
    char fn[5000];
    int pn, ps, nf, ml, n;
    int *d;

    if (parseArguments(argc, argv, fn, &ps, &nf) == -1)
        return -1;

    FILE *f = openFile(fn);

    if (f == NULL)
        return -1;

    d = readDataFromFile(f, &n, ps);

    fclose(f);

    fifo_t *fifo = fifo_constructor(nf);
    ru_t *mru = ru_constructor(nf, 1);
    ru_t *lru = ru_constructor(nf, -1);
    optimal_t *o = optimal_constructor(nf, d, n);

    for (int i = 0; i < n; i++)
    {
        pn = d[i];
        fifo_addToBuffer(fifo, pn);
        ru_addToBuffer(mru, pn);
        ru_addToBuffer(lru, pn);
    }

    optimal_run(o);

    printf("Page Size    # of Pages    Algorithm    Fault Percentage\n");
    optimal_printStatistics(*o, ps);
    fifo_printStatistics(*fifo, ps);
    ru_printStatistics(*lru, ps);
    ru_printStatistics(*mru, ps);

    fifo_destructor(fifo);
    ru_destructor(mru);
    ru_destructor(lru);
    optimal_destructor(o);

    free(d);

    return 0;
}