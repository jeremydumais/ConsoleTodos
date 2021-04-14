#ifndef COMMANDSHOW_H
#define COMMANDSHOW_H

#include "todoList.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int top;
} commandShowArgs;

int parseCommandShow(int argc, char **argv, void **cmdAddArgs);
int executeCommandShow(void **cmdAddArgs, todoList *todos);
void freeCommandShow(void **cmdAddArgs);
void printCommandShowHelp();

#endif