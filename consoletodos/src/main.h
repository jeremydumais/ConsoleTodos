#ifndef CONSOLETODOS_H
#define CONSOLETODOS_H

#include <stdbool.h>

bool analyzeCommand(const char *command);
void printError(const char *error);
void showVersion();

#endif