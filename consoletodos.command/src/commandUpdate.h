#ifndef COMMANDUPDATE_H
#define COMMANDUPDATE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    unsigned int runtimeId;
    bool titleSpecified;
    char *title;
    bool prioritySpecified;
    int priority;
} commandUpdateArgs;

int parseCommandUpdate(int argc, char **argv, void **cmdUpdateArgs);
int executeCommandUpdate(void **cmdUpdateArgs, void **list, size_t *listLength);
void freeCommandUpdate(void **cmdUpdateArgs);
void printCommandUpdateHelp();

#endif