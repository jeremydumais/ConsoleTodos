#ifndef COMMANDADD_H
#define COMMANDADD_H

#include <stdbool.h>

typedef struct {
    char *title;
    int priority;
} commandAddArgs;

int parseCommandAdd(int argc, char **argv, void **cmdAddArgs);
void freeCommandAdd(commandAddArgs **cmdAddArgs);
void printCommandAddHelp();
#endif