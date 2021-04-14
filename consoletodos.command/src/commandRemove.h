#ifndef COMMANDREMOVE_H
#define COMMANDREMOVE_H

#include "todoList.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    unsigned int runtimeId;
} commandRemoveArgs;

int parseCommandRemove(int argc, char **argv, void **cmdRemoveArgs);
int executeCommandRemove(void **cmdRemoveArgs, todoList *todos);
void freeCommandRemove(void **cmdRemoveArgs);
void printCommandRemoveHelp();
#endif