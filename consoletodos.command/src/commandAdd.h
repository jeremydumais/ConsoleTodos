#ifndef COMMANDADD_H
#define COMMANDADD_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    char *title;
    int priority;
} commandAddArgs;

int parseCommandAdd(int argc, char **argv, void **cmdAddArgs);
int executeCommandAdd(void **cmdAddArgs, void **list, size_t *listLength);
void freeCommandAdd(void **cmdAddArgs);
void printCommandAddHelp();
#endif