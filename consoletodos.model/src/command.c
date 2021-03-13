#define __STDC_WANT_LIB_EXT1__ 1
#include "command.h"
#include "commandAdd.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int parseCommand(const char *cmdStr, char *cmd, size_t cmdLength, void **cmdArgs)
{
    if (cmdStr == NULL || cmd == NULL || cmdLength < 1) {
        return E_INVALIDARGS;
    }
    if (strlen(cmdStr) == 0) {
        return E_INVALIDCMD;
    }
    //Retreive the command name
    for (size_t i = 0; i < cmdLength; i++) {
        if (cmdStr[i] == ' ' || i == cmdLength - 1) {
            bool haveReachTheEnd = i == cmdLength - 1;
            const int lastCharAdjustement = (haveReachTheEnd ? 1 : 0);
            strncpy(cmd, cmdStr, i + lastCharAdjustement);
            cmd[i] = '\0';
            break;
        }
    }
    if (!isCommandAvailable(cmd)) {
        return E_INVALIDCMD;
    }
    
    char **argv;
    int argc = _getArgumentsFromString(cmdStr, &argv);
    if (strcmp(cmd, "quit") == 0) {
        *cmdArgs = NULL;
    }
    else if (strcmp(cmd, "help") == 0) {
        *cmdArgs = NULL;
    }
    else if (strcmp(cmd, "version") == 0) {
        *cmdArgs = NULL;
    }
    else if (strcmp(cmd, "add") == 0) {
        int parseResult = parseCommandAdd(argc, argv, cmdArgs);
        if (parseResult != E_SUCCESS) {
            return parseResult;
        }
        /*commandAddArgs *cmdAddArgs = *((commandAddArgs **)cmdArgs);
        printf("%s : %d\n", cmdAddArgs->title, cmdAddArgs->priority);*/

    }

    return E_SUCCESS;
}

bool isCommandAvailable(const char *cmdStr)
{
#define NBCOMMAND 4
    const char *commands[NBCOMMAND] = {
        "quit",
        "help",
        "version",
        "add"};

    if (cmdStr == NULL)
    {
        return false;
    }
    for (int i = 0; i < NBCOMMAND; i++)
    {
        if (strcmp(cmdStr, commands[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

void freeCommand(const char *cmd, void **cmdArgs)
{
    if (strcmp(cmd, "add") == 0) {
        freeCommandAdd((commandAddArgs **)cmdArgs);
    }
}

void printCommandHelp(const char *cmd) 
{
    if (strcmp(cmd, "add") == 0) {
        printCommandAddHelp();
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
    enum states { DULL, IN_WORD, IN_STRING } state = DULL;

    for (p = cmdStr; *p != '\0'; p++) {
        bool haveReachTheEnd = *(p + 1) == '\0';
        const int lastCharAdjustement = (haveReachTheEnd ? 1 : 0);
        c = (unsigned char) *p; /* convert to unsigned char for is* functions */
        switch (state) {
        case DULL: /* not in a word, not in a double quoted string */
            if (isspace(c)) {
                /* still not in a word, so ignore this char */
                continue;
            }
            /* not a space -- if it's a double quote we go to IN_STRING, else to IN_WORD */
            if (c == '"') {
                state = IN_STRING;
                startOfWord = p + 1; /* word starts at *next* char, not this one */
                i = 0;
                continue;
            }
            state = IN_WORD;
            startOfWord = p; /* word starts here */
            if (haveReachTheEnd) {
                //Process the on char word
                
            }
            i = 1;
            continue;

        case IN_STRING:
            /* we're in a double quoted string, so keep going until we hit a close " */
            if (c == '"') {
                /* word goes from start_of_word to p-1 */
                if (itemFound == 0) {
                    (*argv) = malloc(sizeof(char *) * 2);
                }
                else {
                    (*argv) = realloc(*argv, sizeof(char *) * (itemFound + 1));
                }
                (*argv)[itemFound] = malloc(sizeof(char) * i + 1);
                strncpy((*argv)[itemFound], startOfWord, i);
                (*argv)[itemFound][i] = '\0';
                itemFound++;
                state = DULL; /* back to "not in word, not in string" state */
                i = 0;
            }
            else {
                i++;
            }
            continue; /* either still IN_STRING or we handled the end above */

        case IN_WORD:
            /* we're in a word, so keep going until we get to a space */
            if (isspace(c) || *(p + 1) == '\0') {
                /* word goes from start_of_word to p-1 */
                if (itemFound == 0) {
                    (*argv) = malloc(sizeof(char *) * 2);
                }
                else {
                    (*argv) = realloc(*argv, sizeof(char *) * (itemFound + 1));
                }
                (*argv)[itemFound] = malloc(sizeof(char) * i + 1 + lastCharAdjustement);
                strncpy((*argv)[itemFound], startOfWord, i + lastCharAdjustement);
                (*argv)[itemFound][i + lastCharAdjustement] = '\0';
                itemFound++;
                i = 0;
                state = DULL; /* back to "not in word, not in string" state */
            }
            else {
                i++;
            }
            continue; /* either still IN_WORD or we handled the end above */
        }
    }
    return itemFound;
}