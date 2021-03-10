#include "command.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int parseCommand(const char *cmdStr, command *cmd)
{
    if (cmdStr == NULL || cmd == NULL) {
        return E_INVALIDARGS;
    }
    cmd->argc = 0;
    cmd->args = NULL;
    
    bool spacefound;
    bool cmdOrFlagProcessed = false;
    size_t startIndex = 0;
    size_t cmdLength = strlen(cmdStr);
    for(int i = 0; i < cmdLength; i++) {
        if (cmdStr[i] == ' ' || i == cmdLength-1) {
            if (cmd->args == NULL) {
                cmd->args = malloc(sizeof(commandArgument));
            }
            //If this is the first item it represent the command
            if (cmd->argc == 0) {
                cmd->args[0].flag = NULL;
                cmd->args[0].value = malloc(sizeof(char) * (cmdLength-startIndex+1));
                strncpy(cmd->args[0].value, cmdStr + startIndex, cmdLength-startIndex);
            }
            else {

            }
            cmd->argc++;
            break;
        }
    }
    //if (isCommandAvailable())

    return E_SUCCESS;
}

bool isCommandAvailable(const char *cmdStr)
{
    #define NBCOMMAND 4
    const char *commands[NBCOMMAND] = {
        "quit",
        "help",
        "version",
        "add"
    };

    if (cmdStr == NULL) {
        return false;
    }
    for(int i = 0; i < NBCOMMAND; i++) {
        if (strcmp(cmdStr, commands[i]) == 0) {
            return true;
        }
    }
    return false;
}

void freeCommand(command *cmd) 
{
    for(int i = 0; i < cmd->argc; i++) {
        free(cmd->args[i].flag);
        free(cmd->args[i].value);
    }
    free(cmd->args);
}