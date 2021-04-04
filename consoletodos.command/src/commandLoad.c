#include "commandLoad.h"
#include "command.h"
#include "errStorage.h"
#include "todoStorage.h"
#include <stdio.h>

int parseCommandLoad(int argc, char **argv, void **cmdLoadArgs) 
{
    (void)argc; //Not used
    (void)argv; //Not used
    *cmdLoadArgs = NULL;
    return E_SUCCESS;
}

int executeCommandLoad(void **cmdLoadArgs, void **list, size_t *listLength) 
{
    commandLoadArgs *args = *((commandLoadArgs **)cmdLoadArgs);
    int loadResult = loadTodos((args != NULL ? args->filePath : NULL), (todo **)list, listLength);
    if (loadResult != E_TODOSTORAGE_SUCCESS) {
        printError(getLastStorageError());
        return E_EXECUTIONERROR;
    }
    
    printf("%zu todo(s) loaded.\n", *listLength);
    return E_SUCCESS;
}

void freeCommandLoad(void **cmdLoadArgs) 
{
    commandLoadArgs **args = (commandLoadArgs **)cmdLoadArgs;
    if ((*args) != NULL) {
        free((*args)->filePath);
    }
    free(*args);
}