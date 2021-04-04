#ifndef COMMANDSAVE_H
#define COMMANDSAVE_H

#include <stdlib.h>

typedef struct {
    char *filePath;
} commandSaveArgs;

int parseCommandSave(int argc, char **argv, void **cmdSaveArgs);
int executeCommandSave(void **cmdSaveArgs, void **list, size_t *listLength);
void freeCommandSave(void **cmdSaveArgs);

#endif