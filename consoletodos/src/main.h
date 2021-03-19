#ifndef CONSOLETODOS_H
#define CONSOLETODOS_H

#include "todo.h"
#include <stdbool.h>

static todo *todos;
static int todoCount;

bool analyzeCommand(const char *command);
void printError(const char *error);
void showVersion();

#endif