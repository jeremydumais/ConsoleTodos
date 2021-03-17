#ifndef COMMANDADD_H
#define COMMANDADD_H

#include <stdbool.h>

typedef struct {
    char *title;
    int priority;
} commandAddArgs;

int parseCommandAdd(int argc, char **argv, void **cmdAddArgs);
int executeCommandAdd(void **cmdAddArgs);
void freeCommandAdd(void **cmdAddArgs);
void printCommandAddHelp();
#endif