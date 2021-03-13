#include "main.h"
#include "command.h"
#include "todoIO.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define COMMANDSIZE 1024

int main()
{
    bool quit = false;

    while(!quit) {
        char command[COMMANDSIZE];
        printf("❯ ");
        if (getStringValue(command, COMMANDSIZE) == 0) {
            if (!analyzeCommand(command)) {
                quit = true;
                break;
            }
        }
        else {
            printError("Unable to read the command");
            return -1;
        }
    }
    return 0;
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
        else if (strcmp(cmd, "help") == 0) {
            showHelp();
        }
        else if (strcmp(cmd, "version") == 0) {
            showVersion();
        }
        else if (strcmp(cmd, "add") == 0) {
        }
        else {
            printError("Unknown command");
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
    
    return true;
}

void printError(const char *error)
{
    printf("\033[1;31m"); 
    printf("%s\n", error);
    printf("\033[0m"); 
}

void showHelp() 
{
    printf("Available commands\n");
    printf("  help      Display the help (*You are here)\n");
    printf("  version   Display the version of the application\n");
    printf("  quit      Quit the application \n");
}

void showVersion()
{
    printf("Console Todos\n");
    printf("Version 1.0.0\n");
}