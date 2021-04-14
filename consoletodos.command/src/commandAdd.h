#ifndef COMMANDADD_H
#define COMMANDADD_H

#include "todoList.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    char *title;
    int priority;
} commandAddArgs;

int parseCommandAdd(int argc, char **argv, void **cmdAddArgs);
int executeCommandAdd(void **cmdAddArgs, todoList *todos);
void freeCommandAdd(void **cmdAddArgs);
void printCommandAddHelp();
#endif