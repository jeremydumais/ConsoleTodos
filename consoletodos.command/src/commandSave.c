#include "commandSave.h"
#include "command.h"
#include "errStorage.h"
#include "todoStorage.h"
#include <stdio.h>

int parseCommandSave(int argc, char **argv, void **cmdSaveArgs) 
{
    (void)argc; //Not used
    (void)argv; //Not used
    *cmdSaveArgs = NULL;
    return E_SUCCESS;
}

int executeCommandSave(void **cmdSaveArgs, todoList *todos) 
{
    commandSaveArgs *args = *((commandSaveArgs **)cmdSaveArgs);
    int saveResult = saveTodos((args != NULL ? args->filePath : NULL), todos);
    if (saveResult != E_TODOSTORAGE_SUCCESS) {
        printError(getLastStorageError());
        return E_EXECUTIONERROR;
    }
    
    printf("%zu todo(s) saved.\n", todos->length);
    return E_SUCCESS;
}

void freeCommandSave(void **cmdSaveArgs) 
{
    commandSaveArgs **args = (commandSaveArgs **)cmdSaveArgs;
    if ((*args) != NULL) {
        free((*args)->filePath);
    }
    free(*args);
}
