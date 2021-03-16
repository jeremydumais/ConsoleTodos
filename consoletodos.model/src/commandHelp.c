#include "commandHelp.h"
#include "command.h"
#include <stdio.h>

int executeCommandHelp(void **args) 
{
    if (args != NULL) {
        return E_INVALIDARGS;
    }
    printf("Available commands\n");
    printf("  help      Display the help (*You are here)\n");
    printf("  version   Display the version of the application\n");
    printf("  quit      Quit the application \n");   
    return E_SUCCESS;
}
