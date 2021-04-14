#ifndef COMMANDUPDATE_H
#define COMMANDUPDATE_H

#include "todoList.h"
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
int executeCommandUpdate(void **cmdUpdateArgs, todoList *todos);
void freeCommandUpdate(void **cmdUpdateArgs);
void printCommandUpdateHelp();

#endif