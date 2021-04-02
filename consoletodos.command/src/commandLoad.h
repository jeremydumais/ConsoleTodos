#ifndef COMMANDLOAD_H
#define COMMANDLOAD_H

#include <stdlib.h>

typedef struct {
    char *filePath;
} commandLoadArgs;

int parseCommandLoad(int argc, char **argv, void **cmdLoadArgs);
int executeCommandLoad(void **cmdLoadArgs, void **list, size_t *listLength);
void freeCommandLoad(void **cmdLoadArgs);

#endif