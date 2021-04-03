#include "errStorage.h"
#include <linux/limits.h>
#include <stdarg.h>
#include <stdio.h>

#define STORAGEERRORMSG_MAXLEN (PATH_MAX + 1024)

char lastError[STORAGEERRORMSG_MAXLEN];

const char* getLastStorageError() 
{
    return lastError;
}

void setError(const char *format, ...) 
{
    va_list argptr;
    va_start(argptr, format);
    vsnprintf(lastError, STORAGEERRORMSG_MAXLEN, format, argptr);
    va_end(argptr);
}
