#ifndef COMMANDLOAD_H
#define COMMANDLOAD_H

#include "todoList.h"
#include <stdlib.h>

typedef struct {
    char *filePath;
} commandLoadArgs;

int parseCommandLoad(int argc, char **argv, void **cmdLoadArgs);
int executeCommandLoad(void **cmdLoadArgs, todoList *todos);
void freeCommandLoad(void **cmdLoadArgs);

#endif