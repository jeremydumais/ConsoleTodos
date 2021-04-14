#include "commandShow.h"
#include "command.h"
#include "todo.h"
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>

static struct option long_options_show[] =
{
    {"help",     no_argument,       0, '?'},
    {"top",  required_argument, 0, 't'},
    {0, 0, 0, 0}
};

int parseCommandShow(int argc, char **argv, void **cmdAddArgs) 
{
    int c;
    //int top = -1;

    optind = 1;
    while (1)
    {
        /* getopt_long stores the option index here. */
        int option_index = 0;

        c = getopt_long (argc, argv, "?t:",
                         long_options_show, &option_index);

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
            //TODO(task) Check the top value
            break;
            default:
                return E_INVALIDARGS;
        }
    }
    //Check required args
    /*if (title == NULL) {
        return E_REQUIREDARGSMISSING;
    }*/
    *cmdAddArgs = NULL;
    return 0;
}

int executeCommandShow(void **cmdAddArgs, todoList *todos) 
{
    (void)cmdAddArgs; //Not used

    //Print todo header
    for(size_t i = 0; i < todos->length; i++) {
        printf("(%d) %s\n",todos->list[i].runtimeId, todos->list[i].name);
    }
    printf("    %zu todo(s) in your list\n", todos->length);
    return E_SUCCESS;
}

void freeCommandShow(void **cmdAddArgs) 
{
    (void)cmdAddArgs; //Not used
    //TODO(task) Implement the free for that resource
}

void printCommandShowHelp() 
{
    printf("Usage: show -t top [options]\n");
    printf("Options:\n");
    printf("-t, --top=<top>             Show only the x element of the todo list\n");
    printf("-?, --help                  Display the help of the add command\n\n");
}