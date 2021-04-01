#include "main.h"
#include "command.h"
#include "shellUtil.h"
#include "errStorage.h"
#include "todoStorage.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define COMMANDSIZE 1024

int main()
{
    todos = NULL;
    todoCount = 0;

    int initializeStorageResult = launchStorageInitialization();
    if (initializeStorageResult != E_TODOSTORAGE_SUCCESS) {
        printError(getLastStorageError());
        return EXIT_FAILURE;
    }

    bool quit = false;

    while(!quit) {
        char *command = NULL;
        printf("> ");
        if (getStringValue(&command) == 0) {
            if (!analyzeCommand(command)) {
                quit = true;
            }
        }
        else {
            printError("Unable to read the command");
            free(command);
            command = NULL;
            return EXIT_FAILURE;
        }
        free(command);
        command = NULL;
    }
    return EXIT_SUCCESS;
}

bool analyzeCommand(const char *command)
{
    char cmd[COMMANDSIZE];
    void *cmdArgs;
    int parseResult = parseCommand(command, cmd, COMMANDSIZE, &cmdArgs);
    if (parseResult == E_SUCCESS) {
        if (strcmp(cmd, "quit") == 0) {
            return false;
        }
        else if (strcmp(cmd, "version") == 0) {
            showVersion();
        }
        else {
            executeCommand(cmd, &cmdArgs, (void **)&todos, &todoCount);
        }
    }
    else if (parseResult == E_INVALIDCMD) {
        printError("Unknown command");
    }
    else if (parseResult == E_INVALIDARGS) {
        printError("Invalid args");
    }
    else if (parseResult == E_REQUIREDARGSMISSING) {
        printError("Required arguments are missing");
    }
    else if (parseResult == E_DISPLAYHELP) {
        printCommandHelp(cmd);
    }
    
    freeCommand(cmd, &cmdArgs);
    return true;
}

void printError(const char *error)
{
    printf("\033[1;31m"); 
    printf("%s\n", error);
    printf("\033[0m"); 
}

void showVersion()
{
    printf("Console Todos\n");
    printf("Version 1.0.0\n");
}