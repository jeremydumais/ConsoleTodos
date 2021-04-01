#define __STDC_WANT_LIB_EXT1__ 1
#include "command.h"
#include "todoStorage.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

todo *todos;
int todoCount;

static commandDefinition commandDefinitions[COMMANDNB] = {
    {.name = "help", .parseCommand = NULL, .executeCommand = &executeCommandHelp, .printHelp = NULL, .freeCommandArgs = NULL},
    {.name = "quit", .parseCommand = NULL, .executeCommand = NULL, .printHelp = NULL, .freeCommandArgs = NULL},
    {.name = "version", .parseCommand = NULL, .executeCommand = NULL, .printHelp = NULL, .freeCommandArgs = NULL},
    {.name = "add", .parseCommand = &parseCommandAdd, .executeCommand = &executeCommandAdd, .printHelp = &printCommandAddHelp, .freeCommandArgs = &freeCommandAdd},
    {.name = "show", .parseCommand = &parseCommandShow, .executeCommand = &executeCommandShow, .printHelp = &printCommandShowHelp, .freeCommandArgs = NULL},
    {.name = "load", .parseCommand = &parseCommandLoad, .executeCommand = &executeCommandLoad, .printHelp = NULL, .freeCommandArgs = &freeCommandLoad}};

int launchStorageInitialization()
{
    return initializeStorage();
}

int parseCommand(const char *cmdStr, char *cmd, size_t cmdLength, void **cmdArgs)
{
    if (cmdStr == NULL || cmd == NULL || cmdLength < 1)
    {
        return E_INVALIDARGS;
    }
    if (strlen(cmdStr) == 0)
    {
        return E_INVALIDCMD;
    }
    //Retreive the command name
    for (size_t i = 0; i < cmdLength; i++)
    {
        if (cmdStr[i] == ' ' || cmdStr[i] == '\0' || i == cmdLength - 1)
        {
            bool haveReachTheEnd = i == cmdLength - 1;
            const int lastCharAdjustement = (haveReachTheEnd ? 1 : 0);
            strncpy(cmd, cmdStr, i + lastCharAdjustement);
            cmd[i] = '\0';
            break;
        }
    }
    if (!isCommandAvailable(cmd))
    {
        return E_INVALIDCMD;
    }

    int parseResult = E_SUCCESS;
    char **argv = NULL;
    int argc = _getArgumentsFromString(cmdStr, &argv);
    for (int i = 0; i < COMMANDNB; i++) {
        if (strcmp(cmd, commandDefinitions[i].name) == 0) {
            if (commandDefinitions[i].parseCommand != NULL)
            {
                parseResult = (*commandDefinitions[i].parseCommand)(argc, argv, cmdArgs);
                if (parseResult != E_SUCCESS) {
                    break;
                }
            }
            else {
                *cmdArgs = NULL;
            }
            break;
        }
    }
    for(int i=0; i<argc; i++) {
        free(argv[i]);
    }
    free(argv);
    argv = NULL;
    return parseResult;
}

bool isCommandAvailable(const char *cmdStr)
{
    if (cmdStr == NULL)
    {
        return false;
    }
    for (int i = 0; i < COMMANDNB; i++)
    {
        if (strcmp(cmdStr, commandDefinitions[i].name) == 0)
        {
            return true;
        }
    }
    return false;
}

void executeCommand(const char *cmd, void **cmdArgs, void **list, int *listLength)
{
    for (int i = 0; i < COMMANDNB; i++)
    {
        if (strcmp(cmd, commandDefinitions[i].name) == 0)
        {
            int (*executeFunction)(void **cmdAddArgs, void **list, int *listLength) = commandDefinitions[i].executeCommand;
            if (executeFunction != NULL)
            {
                (*commandDefinitions[i].executeCommand)(cmdArgs, list, listLength);
            }
            break;
        }
    }
}

void freeCommand(const char *cmd, void **cmdArgs)
{
    for (int i = 0; i < COMMANDNB; i++)
    {
        if (strcmp(cmd, commandDefinitions[i].name) == 0)
        {
            void (*freeFunction)(void **cmdAddArgs) = commandDefinitions[i].freeCommandArgs;
            if (freeFunction != NULL && (*cmdArgs) != NULL) {
                (*freeFunction)(cmdArgs);
            }
            break;
        }
    }
}

void printCommandHelp(const char *cmd)
{
    for (int i = 0; i < COMMANDNB; i++)
    {
        if (strcmp(cmd, commandDefinitions[i].name) == 0)
        {
            void (*helpFunction)() = commandDefinitions[i].printHelp;
            if (helpFunction != NULL)
                (*helpFunction)();
            break;
        }
    }
}

int _getArgumentsFromString(const char *cmdStr, char ***argv)
{
    //https://stackoverflow.com/questions/9659697/parse-string-into-array-based-on-spaces-or-double-quotes-strings
    const char *p;
    const char *startOfWord = NULL;
    int c;
    int i = 0;
    int itemFound = 0;
    enum states
    {
        DULL,
        IN_WORD,
        IN_STRING
    } state = DULL;

    for (p = cmdStr; *p != '\0'; p++)
    {
        bool haveReachTheEnd = *(p + 1) == '\0';
        const int lastCharAdjustement = (haveReachTheEnd ? 1 : 0);
        c = (unsigned char)*p; /* convert to unsigned char for is* functions */
        switch (state)
        {
        case DULL: /* not in a word, not in a double quoted string */
            if (isspace(c))
            {
                /* still not in a word, so ignore this char */
                continue;
            }
            /* not a space -- if it's a double quote we go to IN_STRING, else to IN_WORD */
            if (c == '"')
            {
                state = IN_STRING;
                startOfWord = p + 1; /* word starts at *next* char, not this one */
                i = 0;
                continue;
            }
            state = IN_WORD;
            startOfWord = p; /* word starts here */
            if (haveReachTheEnd)
            {
                //The argument as only on char and this is the last char
                p--; //Reprocess the last character as a Word
            }
            i = 1;
            continue;

        case IN_STRING:
            /* we're in a double quoted string, so keep going until we hit a close " */
            if (c == '"')
            {
                /* word goes from start_of_word to p-1 */
                if (itemFound == 0)
                {
                    (*argv) = malloc(sizeof(char *));
                }
                else
                {
                    (*argv) = realloc(*argv, sizeof(char *) * (itemFound + 1));
                }
                (*argv)[itemFound] = malloc(sizeof(char) * i + 1);
                strncpy((*argv)[itemFound], startOfWord, i);
                (*argv)[itemFound][i] = '\0';
                itemFound++;
                state = DULL; /* back to "not in word, not in string" state */
                i = 0;
            }
            else
            {
                i++;
            }
            continue; /* either still IN_STRING or we handled the end above */

        case IN_WORD:
            /* we're in a word, so keep going until we get to a space */
            if (isspace(c) || *(p + 1) == '\0')
            {
                /* word goes from start_of_word to p-1 */
                if (itemFound == 0)
                {
                    (*argv) = malloc(sizeof(char *));
                }
                else
                {
                    (*argv) = realloc(*argv, sizeof(char *) * (itemFound + 1));
                }
                (*argv)[itemFound] = malloc(sizeof(char) * i + 1 + lastCharAdjustement);
                strncpy((*argv)[itemFound], startOfWord, i + lastCharAdjustement);
                (*argv)[itemFound][i + lastCharAdjustement] = '\0';
                itemFound++;
                i = 0;
                state = DULL; /* back to "not in word, not in string" state */
            }
            else
            {
                i++;
            }
            continue; /* either still IN_WORD or we handled the end above */
        }
    }
    return itemFound;
}
