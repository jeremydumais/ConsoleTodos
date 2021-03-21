#ifndef COMMANDSHOW_H
#define COMMANDSHOW_H

#include <stdbool.h>

typedef struct {
    int top;
} commandShowArgs;

int parseCommandShow(int argc, char **argv, void **cmdAddArgs);
int executeCommandShow(void **cmdAddArgs, void **list, int *listLength);
void freeCommandShow(void **cmdAddArgs);
void printCommandShowHelp();

#endif