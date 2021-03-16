#include "todoIO.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getStringValue(char **value)
{
    if (((*value) = readline(NULL)) != NULL) {
        add_history((*value));
        return 0;
    }
    else {
        return -1;
    }
}

int getIntValue(int *value)
{
    const int MAXLENGTH = 10;
    char valueStr[MAXLENGTH];
    if (fgets(valueStr, MAXLENGTH, stdin) != NULL) {
        valueStr[strcspn(valueStr, "\n")] = 0;
        *value = atoi(valueStr);
        if (*value == 0) {
            return -1;
        }
        return 0;
    }
    else {
        return -1;
    }
}