#include "commandLoad.h"
#include "command.h"
#include "errStorage.h"
#include "todoStorage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parseCommandLoad(int argc, char **argv, void **cmdLoadArgs) 
{
    /*
    *cmdLoadArgs = malloc(sizeof(commandLoadArgs));
    commandLoadArgs *args = *((commandLoadArgs **)cmdLoadArgs);
    const char *storageTodoFileName = getStorageTodoFileName();
    int todoFileNameLength = strlen(storageTodoFileName);
    args->filePath = malloc(sizeof(char) * (todoFileNameLength + 1));
    strcpy(args->filePath, storageTodoFileName);*/
    (void)argc; //Not used
    (void)argv; //Not used
    *cmdLoadArgs = NULL;
    return E_SUCCESS;
}

int executeCommandLoad(void **cmdLoadArgs, void **list, size_t *listLength) 
{
    commandLoadArgs *args = *((commandLoadArgs **)cmdLoadArgs);
    int loadResult = loadTodos((args != NULL ? args->filePath : NULL), (todo **)list, listLength);
    if (loadResult == E_TODOSTORAGE_SUCCESS) {
        printf("%zu todo(s) loaded.\n", *listLength);
        return E_SUCCESS;
    }
    else {
        printError(getLastStorageError());
        return E_EXECUTIONERROR;
    }
}

void freeCommandLoad(void **cmdLoadArgs) 
{
    commandLoadArgs **args = (commandLoadArgs **)cmdLoadArgs;
    if ((*args) != NULL) {
        free((*args)->filePath);
    }
    free(*args);
}