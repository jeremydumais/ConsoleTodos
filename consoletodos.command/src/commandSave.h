#ifndef COMMANDSAVE_H
#define COMMANDSAVE_H

#include "todoList.h"
#include <stdlib.h>

typedef struct {
    char *filePath;
} commandSaveArgs;

int parseCommandSave(int argc, char **argv, void **cmdSaveArgs);
int executeCommandSave(void **cmdSaveArgs, todoList *todos);
void freeCommandSave(void **cmdSaveArgs);

#endif