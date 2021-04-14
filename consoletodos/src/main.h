#ifndef CONSOLETODOS_H
#define CONSOLETODOS_H

#include "todoList.h"
#include <stdbool.h>
#include <stdlib.h>

bool analyzeCommand(const char *command, todoList *todos);
void showVersion();

#endif