#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int, int);
int min(int, int);

int calculatePageNumber(int, int);
int valueInArray(int, int *, int);

int parseArguments(int, char **, char *, int *, int *);

FILE *openFile(char *);
int *readDataFromFile(FILE *, int *, int);

int *intArray_constructor(int);
void intArray_destructor(int *);

#endif