#ifndef COMMANDLOAD_H
#define COMMANDLOAD_H

typedef struct {
    char *filePath;
} commandLoadArgs;

int parseCommandLoad(int argc, char **argv, void **cmdLoadArgs);
int executeCommandLoad(void **cmdLoadArgs, void **list, int *listLength);
void freeCommandLoad(void **cmdLoadArgs);

#endif