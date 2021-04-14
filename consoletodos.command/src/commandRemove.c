#include "commandRemove.h"
#include "command.h"
#include "todo.h"
#include "todoStorage.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

static struct option long_options_remove[] =
{
    {"help",     no_argument,       0, '?'},
    {"id",  required_argument, 0, 'i'},
    {0, 0, 0, 0}
};

int parseCommandRemove(int argc, char **argv, void **cmdRemoveArgs) 
{
    int c;
    unsigned int runtimeId = 0;

    optind = 1;
    while (1)
    {
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "?i:",
                         long_options_remove, &option_index);

        /* Detect the end of the options. */
        if (c == -1) {
            break;
        }
        switch (c)
        {
            case '?':
                return E_DISPLAYHELP;
            break;
            case 'i':
                runtimeId = (unsigned int)strtoul(optarg, NULL, BASE10);
            break;
            default:
                return E_INVALIDARGS;
        }
    }
    //Check required args
    if (runtimeId == 0) {
        return E_REQUIREDARGSMISSING;
    }
    *cmdRemoveArgs = malloc(sizeof(commandRemoveArgs));
    commandRemoveArgs *args = *((commandRemoveArgs **)cmdRemoveArgs);
    args->runtimeId = runtimeId;
    return E_SUCCESS;
}

int executeCommandRemove(void **cmdRemoveArgs, void **list, size_t *listLength) 
{
    /*commandAddArgs *args = *((commandAddArgs **)cmdAddArgs);
    if (*list == NULL) {
        *list = malloc(sizeof(todo));
    }
    else {
        *list = realloc(*list, sizeof(todo) * ((*listLength) + 1));
    }

    todo *todos = *((todo **)list);
    if (createTodo(todos + (*listLength), args->title) == 0) {
        (*listLength)++;
    }
    else {
        printError("Unable to create the todo");
    }
    */
    return E_SUCCESS;
}

void freeCommandRemove(void **cmdRemoveArgs) 
{
    commandRemoveArgs **args = (commandRemoveArgs **)cmdRemoveArgs;
    free((*args));
    *args = NULL;
}

void printCommandRemoveHelp() 
{
    printf("Usage: remove -i runtimeId\n");
    printf("Options:\n");
    printf("-i, --id=<runtimeId>        The runtime id of the todo\n");
    printf("-?, --help                  Display the help of the add command\n\n");
}
