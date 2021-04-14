#include "commandHelp.h"
#include "command.h"
#include <stdio.h>

int executeCommandHelp(void **args, void **list, size_t *listLength) 
{
    if (*args != NULL) {
        return E_INVALIDARGS;
    }
    (void)list; //Not used
    (void)listLength; //Not used

    printf("Available commands\n");
    printf("  add       Add a new todo\n");   
    printf("  update    Update the fields of a todo\n");   
    printf("  remove    Remove a todo\n");   
    printf("  show      Print the todo list\n");   
    printf("  load      Load the list of todos\n");
    printf("  save      Save the list of todos\n");
    printf("  help      Display the help (*You are here)\n");
    printf("  version   Display the version of the application\n");
    printf("  quit      Quit the application\n");   
    return E_SUCCESS;
}
