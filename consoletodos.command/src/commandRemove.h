#ifndef COMMANDREMOVE_H
#define COMMANDREMOVE_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    unsigned int runtimeId;
} commandRemoveArgs;

int parseCommandRemove(int argc, char **argv, void **cmdRemoveArgs);
int executeCommandRemove(void **cmdRemoveArgs, void **list, size_t *listLength);
void freeCommandRemove(void **cmdRemoveArgs);
void printCommandRemoveHelp();
#endif