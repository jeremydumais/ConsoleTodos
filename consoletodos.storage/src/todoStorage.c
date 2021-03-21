#include "todoStorage.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int initializeStorage() 
{
    //Get home directory
    const char *home = getenv("HOME");
    strcpy(configDirectory, home);
    //Check if the config folder exist (~/.config/ConsoleTodos), if not try create it
    strcat(configDirectory, "/.config/ConsoleTodos");
    if (!_directoryExist(configDirectory)) {
        //Try to create the ConsoleTodos directory
        if (mkdir(configDirectory, 0700) == -1) {
            sprintf(lastStorageError, "Unable to create the config directory %s.\nInternal error: %s", configDirectory, strerror(errno));
            return E_STORAGECONFIGDIRCREATEDENIED;
        }
    }
    //Check if the config file exist, if not create it (~/.config/ConsoleTodos/consoletodos.conf)
    strcpy(configFilePath, configDirectory);
    strcat(configFilePath, "/consoletodos.conf");
    if (!_fileExist(configFilePath)) {
        if(createNewConfigFile(configFilePath, configDirectory) != E_STORAGESUCCESS) {
            sprintf(lastStorageError, "Unable to create the config file %s.\nInternal error: %s", configFilePath, strerror(errno));
            return E_STORAGECONFIGFILECREATEERROR;
        }
    }
    //TODO Load the todo file location from the config file
    strcpy(todoFileName, configDirectory);
    strcat(todoFileName, "/todos.json");
    
    return E_STORAGESUCCESS;
}

int loadTodos(const char *filePath, todo **list, int *listLength) 
{
    //TODO free old list if not NULL
    *listLength = 0;

    if (*list == NULL) {
        *list = malloc(sizeof(todo));
    }
    todo *todos = *((todo **)list);
    size_t titleLength = strlen("Test");
    todos[*listLength].name = malloc(sizeof(char) * (titleLength + 1));
    strcpy(todos[*listLength].name, "Test");
    todos[*listLength].name[titleLength] = 0;
    (*listLength)++;
    return E_STORAGESUCCESS;
}

int saveTodos(todo **list, int listLength) 
{
    return 0;
}

const char* getLastStorageError() 
{
    return lastStorageError;
}

const char *getStorageTodoFileName()
{
    return todoFileName;
}

bool _directoryExist(const char *folderPath) 
{
    struct stat sb;
    if (stat(folderPath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        return true;
    }
    return false;
}

bool _fileExist(const char *filePath) 
{
    struct stat sb;
    if (stat(filePath, &sb) == 0 && S_ISREG(sb.st_mode)) {
        return true;
    }
    return false;
}

int createNewConfigFile(const char *filePath, const char *configDirectory) 
{
    FILE *configFile = fopen(filePath, "w+");
    if (configFile == NULL) {
        return E_STORAGECONFIGFILECREATEERROR;
    }
    //Write the default config file
    char fileContent[PATH_MAX + 1024];
    sprintf(fileContent, "# Console todos config file\n\n\
todosFilePath = %s/todos.json\n", configDirectory);
    if (fputs(fileContent, configFile) < 0) {
        fclose(configFile);
        return E_STORAGECONFIGFILECREATEERROR;
    }
    
    fclose(configFile);
    return E_STORAGESUCCESS;
}