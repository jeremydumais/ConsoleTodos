#ifndef CONSOLETODOS_H
#define CONSOLETODOS_H

#include <stdbool.h>
#include <stdlib.h>

bool analyzeCommand(const char *command, void **list, size_t *listLength);
void showVersion();

#endif