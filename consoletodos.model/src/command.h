#ifndef COMMAND_H
#define COMMAND_H

typedef struct {
    int argc;
    char **argv;
} command;

enum _command_error {
    E_SUCCESS = 0,
    E_INVALID_COMMAND = -1,
    E_INVALID_ARGS = -2
};

int parseCommand(const char *cmdStr, command *cmd);

#endif