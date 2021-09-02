#include "helpers.h"

/**
 * Returns the maximum value of two integers.
 *
 * @param a a value
 * @param b another value
 *
 * @return the maximum of a or b
 */
int max(int a, int b)
{
    return (a > b) ? a : b;
}

/**
 * Returns the minimum value of two integers.
 *
 * @param a a value
 * @param b another value
 *
 * @return the minimum of a or b
 */
int min(int a, int b)
{
    return (a < b) ? a : b;
}

/**
 * Calculates the page number from memory address and page size
 *
 * @param ma the memory address
 * @param ps the page size
 *
 * @return the integer division of memory address and page size
 */
int calculatePageNumber(int ma, int ps)
{
    return ma / ps;
}

/**
 * Checks whether a value is contained in an array.
 *
 * @param v the value to look for
 * @param a the array to search
 * @param la the length of array a
 *
 * @return 1 if v is a member of a, 0 otherwise
 */
int valueInArray(int v, int *a, int la)
{
    int b = 0;
    for (int i = 0; i < la; i++)
        b = max(b, a[i] == v);

    return b;
}

/**
 * Parses positional command-line arguments.
 *
 * @param argc argc from program input
 * @param argv argv from program input
 * @param fn a character array for storing the filename
 * @param ps an integer to store page size
 * @param nf an integer to store number of frames
 *
 * @return -1 if error, 0 otherwise
 */
int parseArguments(int argc, char **argv, char *fn, int *ps, int *nf)
{
    int tmp;
    if (argc < 4)
        return -1;

    strcpy(fn, argv[1]);
    tmp = atoi(argv[2]);
    *ps = tmp;
    tmp = atoi(argv[3]);
    *nf = tmp;

    return 0;
}

/**
 * Opens the file specified by character array.
 *
 * @param fn the name of the file
 *
 * @return a file pointer
 */
FILE *openFile(char *fn)
{
    FILE *f = fopen(fn, "r");
    if (f == NULL)
        printf("No file named %s found.\n", fn);

    return f;
}

/**
 * Reads data data from file into an integer array.
 *
 * @param f a file pointer
 * @param n an integer to store the number of elements read in from file
 *
 * @return a pointer to the array of elements contained in the file
 */
int *readDataFromFile(FILE *f, int *n, int ps)
{
    int tmp, s = 1;
    int *d = calloc(s, sizeof(int));
    *n = 0;
    while (!feof(f))
    {
        fscanf(f, "%d\n", &tmp);
        d[(*n)++] = tmp / ps;
        if (*n >= s)
        {
            s *= 2;
            d = realloc(d, s * sizeof(int));
        }
    }

    d = realloc(d, *n * sizeof(int));
    return d;
}

/**
 * Allocates an array of integers.
 *
 * @param c the number of elements to allocate
 *
 * @return a pointer to the allocated array
 */
int *intArray_constructor(int c)
{
    return calloc(c, sizeof(unsigned int));
}

/**
 * Frees the memory allocated by intArray_constructor
 *
 * @param a the array to free
 */
void intArray_destructor(int *a)
{
    free(a);
}