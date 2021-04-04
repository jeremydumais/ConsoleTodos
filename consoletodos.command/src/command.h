#ifndef COMMAND_H
#define COMMAND_H

#include "commandAdd.h"
#include "commandHelp.h"
#include "commandLoad.h"
#include "commandSave.h"
#include "commandShow.h"
#include "commandUpdate.h"
#include "commandUtil.h"
#include "todo.h"
#include <stdbool.h>
#include <stddef.h>

#define COMMANDNB 8

typedef struct {
    char *name;
    int (*parseCommand)(int argc, char **argv, void **cmdAddArgs);
    int (*executeCommand)(void **cmdAddArgs, void **list, size_t *listLength);
    void (*printHelp)();
    void (*freeCommandArgs)(void **cmdAddArgs);
    
} commandDefinition;

enum _command_error {
    E_SUCCESS = 0,
    E_INVALIDCMD = -1,
    E_INVALIDARGS = -2,
    E_REQUIREDARGSMISSING = -3,
    E_DISPLAYHELP = -4,
    E_EXECUTIONERROR = -5
};

int launchStorageInitialization();
int parseCommand(const char *cmdStr, char *cmd, size_t cmdLength, void **cmdArgs);
bool isCommandAvailable(const char *cmdStr);
void executeCommand(const char *cmd, void **cmdArgs, void **list, size_t *listLength);
void freeCommand(const char *cmd, void **cmdArgs);
void printCommandHelp(const char *cmd);

#endif