#ifndef COMMAND_H
#define COMMAND_H

#include <stdbool.h>

typedef struct {
    char *flag;
    char *value;
} commandArgument;

typedef struct {
    int argc;
    commandArgument *args;
} command;

enum _command_error {
    E_SUCCESS = 0,
    E_INVALIDCMD = -1,
    E_INVALIDARGS = -2
};

int parseCommand(const char *cmdStr, command *cmd);
bool isCommandAvailable(const char *cmdStr);
void freeCommand(command *cmd);

#endif