#include "commandUtil.h"
#include <stdarg.h>
#include <stdio.h>

void printError(const char *error, ...)
{

    va_list argptr;
    va_start(argptr, error);
    printf("\033[1;31m"); 
    vprintf(error, argptr);
    printf("\n");
    printf("\033[0m"); 
    va_end(argptr);
}