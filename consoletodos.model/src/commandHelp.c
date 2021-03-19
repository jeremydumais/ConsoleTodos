#include "commandHelp.h"
#include "command.h"
#include <stdio.h>

int executeCommandHelp(void **args, void **list, int *listLength) 
{
    if (*args != NULL) {
        return E_INVALIDARGS;
    }
    printf("Available commands\n");
    printf("  add       Add a new todo\n");   
    printf("  show      Print the todo list\n");   
    printf("  help      Display the help (*You are here)\n");
    printf("  version   Display the version of the application\n");
    printf("  quit      Quit the application\n");   
    return E_SUCCESS;
}
