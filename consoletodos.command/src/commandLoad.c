#include "commandLoad.h"
#include "command.h"
#include "todoStorage.h"
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
    *cmdLoadArgs = NULL;
    return E_SUCCESS;
}

int executeCommandLoad(void **cmdLoadArgs, void **list, int *listLength) 
{
    commandLoadArgs *args = *((commandLoadArgs **)cmdLoadArgs);
    int loadResult = loadTodos((args != NULL ? args->filePath : NULL), (todo **)list, listLength);
    if (loadResult == E_STORAGESUCCESS) {
        return E_SUCCESS;
    }
    else {
        //TODO return the corresponding error value
        return -1;
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


