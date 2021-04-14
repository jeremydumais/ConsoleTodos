#include "commandUpdate.h"
#include "command.h"
#include "todo.h"
#include "todoStorage.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

static struct option long_options_update[] =
{
    {"help",     no_argument,       0, '?'},
    {"id",  required_argument, 0, 'i'},
    {"title",  required_argument, 0, 't'},
    {"priority",  required_argument, 0, 'p'},
    {0, 0, 0, 0}
};

int parseCommandUpdate(int argc, char **argv, void **cmdUpdateArgs) 
{
    int c;
    unsigned int runtimeId = 0;
    bool titleSpecified = false;
    char *title = NULL;
    bool prioritySpecified = false;
    int priority = 3;
    int updateOptionsSpecified = 0;

    optind = 1;
    while (1)
    {
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "?i:t:p:",
                         long_options_update, &option_index);

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
            case 't':
                title = optarg;
                titleSpecified = true;
                updateOptionsSpecified++;
            break;
            case 'p':
                prioritySpecified = true;
                updateOptionsSpecified++;
            break;
            default:
                return E_INVALIDARGS;
        }
    }
    //Check required args
    if (runtimeId == 0 || updateOptionsSpecified == 0) {
        return E_REQUIREDARGSMISSING;
    }
    *cmdUpdateArgs = malloc(sizeof(commandUpdateArgs));
    commandUpdateArgs *args = *((commandUpdateArgs **)cmdUpdateArgs);
    args->runtimeId = runtimeId;
    args->titleSpecified = titleSpecified;
    if (args->titleSpecified) {
        size_t titleLength = strlen(title);
        args->title = malloc(sizeof(char) * (titleLength + 1));
        strncpy(args->title, title, titleLength);
        args->title[titleLength] = '\0';
    }
    else {
        args->title = NULL;
    }
    args->prioritySpecified = prioritySpecified;
    if (args->prioritySpecified) {
        args->priority = priority;
    }
    return E_SUCCESS;
}

int executeCommandUpdate(void **cmdUpdateArgs, todoList *todos) 
{
    commandUpdateArgs *args = *((commandUpdateArgs **)cmdUpdateArgs);
    todo *todoToUpdate = NULL;
    //Find the todo to update
    for(size_t i = 0; i < todos->length; i++) {
        if (todos->list[i].runtimeId == args->runtimeId) {
            todoToUpdate = todos->list + i;
            break;
        }
    }
    if (todoToUpdate == NULL) {
        printError("Unable to find the todo with runtime id %zu", args->runtimeId);
        return E_EXECUTIONERROR;
    }

    if (!updateTodo(todoToUpdate, args->title) == 0) {
        printError("Unable to update the todo");
    }
    return E_SUCCESS;
}

void freeCommandUpdate(void **cmdUpdateArgs) 
{
    commandUpdateArgs **args = (commandUpdateArgs **)cmdUpdateArgs;
    free((*args)->title);
    free((*args));
    *args = NULL;
}

void printCommandUpdateHelp() 
{
    printf("Usage: update -i runtimeId [-t title] [-p priority]\n");
    printf("Options:\n");
    printf("-i, --id=<runtimeId>        The runtime id of the todo\n");
    printf("-t, --title=<title>         The title of the todo\n");
    printf("-p, --priority=<priority>   The priority of the todo (Starting at 1)\n");
    printf("-?, --help                  Display the help of the Update command\n\n");
}
