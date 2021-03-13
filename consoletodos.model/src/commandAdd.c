#include "commandAdd.h"
#include "command.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

static struct option long_options_add[] =
{
    {"help",     no_argument,       0, '?'},
    {"title",  required_argument, 0, 't'},
    {"priority",  required_argument, 0, 'p'},
    {0, 0, 0, 0}
};

int parseCommandAdd(int argc, char **argv, void **cmdAddArgs) 
{
    int c;
    char *title = NULL;
    int priority = 3;

    optind = 1;
    while (1)
    {
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "?t:p:",
                         long_options_add, &option_index);

        /* Detect the end of the options. */
        if (c == -1) {
            break;
        }

        switch (c)
        {
            case '?':
                return E_DISPLAYHELP;
            break;
            case 't':
            //Check the the title is not empty
            title = optarg;
            break;
            case 'p':
            break;
            default:
                return E_INVALIDARGS;
        }
    }
    //Check required args
    if (title == NULL) {
        return E_REQUIREDARGSMISSING;
    }
    *cmdAddArgs = malloc(sizeof(commandAddArgs));
    commandAddArgs *args = *((commandAddArgs **)cmdAddArgs);
    int titleLength = strlen(title);
    args->title = malloc(sizeof(char) * (titleLength + 1));
    strncpy(args->title, title, titleLength);
    args->title[titleLength] = '\0';
    args->priority = priority;
    return 0;
}

void freeCommandAdd(commandAddArgs **cmdAddArgs) 
{
    free((*cmdAddArgs)->title);
    free(*cmdAddArgs);
}

void printCommandAddHelp() 
{
    printf("Usage: add -t title [options]\n");
    printf("Options:\n");
    printf("-t, --title=<title>         The title of the todo\n");
    printf("-p, --priority=<priority>   The priority of the todo (Starting at 1)\n");
    printf("-?, --help                  Display the help of the add command\n\n");

}
