#ifndef COMMANDSHOW_H
#define COMMANDSHOW_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int top;
} commandShowArgs;

int parseCommandShow(int argc, char **argv, void **cmdAddArgs);
int executeCommandShow(void **cmdAddArgs, void **list, size_t *listLength);
void freeCommandShow(void **cmdAddArgs);
void printCommandShowHelp();

#endif