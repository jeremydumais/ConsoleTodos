#include "todoIO.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getStringValue(char *value, const int MAXLENGTH)
{
    if (fgets(value, MAXLENGTH, stdin) != NULL) {
        value[strcspn(value, "\n")] = 0;
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