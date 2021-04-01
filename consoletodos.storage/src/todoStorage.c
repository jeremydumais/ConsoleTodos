#include "todoStorage.h"
#include "configStorage.h"
#include "errStorage.h"
#include "json.h"
#include "json_object.h"
#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static char todoFileName[PATH_MAX + 1];
static char configDirectory[PATH_MAX + 1];
static char configFilePath[PATH_MAX + 1];

bool directoryExist(const char *folderPath);
bool fileExist(const char *filePath);

int initializeStorage() 
{
    //Get home directory
    const char *home = getenv("HOME");
    strcpy(configDirectory, home);
    //Check if the config folder exist (~/.config/ConsoleTodos), if not try create it
    strcat(configDirectory, "/.config/ConsoleTodos");
    if (!directoryExist(configDirectory)) {
        //Try to create the ConsoleTodos directory
        if (mkdir(configDirectory, 0700) == -1) {
            setError("Unable to create the config directory %s.\nInternal error: %s", configDirectory, strerror(errno));
            return E_TODOSTORAGE_ERROR;
        }
    }
    //Check if the config file exist, if not create it (~/.config/ConsoleTodos/consoletodos.conf)
    strcpy(configFilePath, configDirectory);
    strcat(configFilePath, "/consoletodos.conf");
    if (!fileExist(configFilePath)) {
        if(createNewConfigFile(configFilePath, configDirectory) != E_TODOSTORAGE_SUCCESS) {
            setError("Unable to create the config file %s.\nInternal error: %s", configFilePath, strerror(errno));
            return E_TODOSTORAGE_ERROR;
        }
    }

    if (openConfigFile(configFilePath) != E_CONFIGSTORAGE_SUCCESS) {
        setError("Unable to open the config file %s.\nInternal error: %s", configFilePath, strerror(errno));
        return E_TODOSTORAGE_ERROR;
    }
    if (readConfigFileStringValue("todosFilePath", todoFileName, PATH_MAX + 1) != E_CONFIGSTORAGE_SUCCESS) {
        setError("Unable to find a value for the item todosFilePath in the config file %s.\nInternal error: %s", configFilePath, strerror(errno));
        return E_TODOSTORAGE_ERROR;
    }

    if (closeConfigFile() != E_CONFIGSTORAGE_SUCCESS) {
        setError("Unable to close the config file %s.\nInternal error: %s", configFilePath, strerror(errno));
        return E_TODOSTORAGE_ERROR;
    }
    
    return E_TODOSTORAGE_SUCCESS;
}

int loadTodos(const char *filePath, todo **list, int *listLength) 
{
    //TODO free old list if not NULL

    //TODO open the todo file
    struct json_object *item = json_object_new_object();
    json_object_object_add(item, "test", json_object_new_string("valeur"));
    const char *t = json_object_to_json_string_ext(item, JSON_C_TO_STRING_PRETTY);
    printf("%s\n", t);
    json_object_put(item);
    item = NULL;
    *listLength = 0;

    if (*list == NULL) {
        *list = malloc(sizeof(todo));
        //(*list)[0].name = malloc(256);
    }  
    (*listLength)++;
    return E_TODOSTORAGE_SUCCESS;
}

/*int saveTodos(todo **list, int listLength) 
{
    (void)list;
    (void)listLength;
    return 0;
}*/

const char *getStorageTodoFileName()
{
    return todoFileName;
}

bool directoryExist(const char *folderPath) 
{
    struct stat sb;
    if (stat(folderPath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
        return true;
    }
    return false;
}

bool fileExist(const char *filePath) 
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
        return E_TODOSTORAGE_ERROR;
    }
    //Write the default config file
    char fileContent[PATH_MAX + 1024];
    sprintf(fileContent, "# Console todos config file\n\n\
todosFilePath = %s/todos.json\n", configDirectory);
    if (fputs(fileContent, configFile) < 0) {
        fclose(configFile);
        return E_TODOSTORAGE_ERROR;
    }
    
    fclose(configFile);
    return E_TODOSTORAGE_SUCCESS;
}
