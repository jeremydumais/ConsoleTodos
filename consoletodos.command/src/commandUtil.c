#include "commandUtil.h"
#include <stdio.h>

void printError(const char *error)
{
    printf("\033[1;31m"); 
    printf("%s\n", error);
    printf("\033[0m"); 
}