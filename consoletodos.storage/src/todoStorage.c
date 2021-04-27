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

#define DEFAULTCONFIGFILEMAXSIZE (PATH_MAX + 1024)
static char todoFileName[PATH_MAX + 1];
static char configDirectory[PATH_MAX + 1];
static char configFilePath[PATH_MAX + 1];

bool createTodosFromJSONString(const char *fileContent, todoList *todos);
char *createJSONStringFromTodos(const todoList *todos);
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

int loadTodos(const char *filePath, todoList *todos) 
{
    freeTodoList(todos);
    //If no file path was specified, use the one from the config file
    if (filePath == NULL) {
        filePath = todoFileName;
    }
    //Read the entire todo list file
    FILE *todoFile = fopen(filePath, "r");
    if (!todoFile) {
        setError("Unable to open the todo file %s.\nInternal error: %s", filePath, strerror(errno));
        return E_TODOSTORAGE_ERROR;
    }
    fseek(todoFile, 0, SEEK_END);
    long todoFileSize = ftell(todoFile);
    fseek(todoFile, 0, SEEK_SET);

    char *fileContent = malloc(todoFileSize + 1);
    fread(fileContent, sizeof(char), todoFileSize, todoFile);
    fclose(todoFile);
    fileContent[todoFileSize] = '\0';
    bool creationResult = createTodosFromJSONString(fileContent, todos);
    free(fileContent);
    if (!creationResult) {
        return E_TODOSTORAGE_ERROR;
    }

    return E_TODOSTORAGE_SUCCESS;
}

bool createTodosFromJSONString(const char *fileContent, todoList *todos)
{
    if (fileContent == NULL) {
        setError("The file content is null");
        return false;
    }
    //Parse the file content to a json_object struct
    struct json_object *jsonObj = json_tokener_parse(fileContent);
    if (json_object_get_type(jsonObj) != json_type_array) {
        json_object_put(jsonObj);
        setError("The file content is not a json array");
        return false;
    }
    size_t fileTodosCount = json_object_array_length(jsonObj);
    if (fileTodosCount == 0) {
        json_object_put(jsonObj);
        return true;
    }

    bool anErrorOccured = false;
    for(size_t i = 0; i < fileTodosCount; i++) {
        struct json_object *todoJSONObj = json_object_array_get_idx(jsonObj, i);
        if (todoJSONObj != NULL) {
            struct json_object *todoJSONObjNameField = json_object_object_get(todoJSONObj, "name");
            if (todoJSONObjNameField == NULL) {
                //TODO to be tested
                anErrorOccured = true;
                setError("The todo item json string doesn't contains a field \"name\" : %s", json_object_to_json_string(todoJSONObj));
                break;
            }
            const char *todoNameValue = json_object_get_string(todoJSONObjNameField);
            todo *todoItem = createTodo(todoNameValue);
            if (todoItem == NULL) {
                anErrorOccured = true;
                //TODO to be tested
                setError("Cannot create a todo item from the string %s", todoNameValue);
                break;
            }
            if (appendTodo(todos, todoItem) != 0) {
                anErrorOccured = true;
                //TODO to be tested
                setError("Cannot add the todo item %s to the list", todoNameValue);
                break;
            }
            freeTodo(&todoItem);
        }
    }
    if (anErrorOccured) {
        freeTodoList(todos);
        return false;
    }
    //Free the acquires ressources
    json_object_put(jsonObj);
    jsonObj = NULL;
    return true;
}

int saveTodos(const char *filePath, const todoList *todos) 
{
    //If no file path was specified, use the one from the config file
    if (filePath == NULL) {
        filePath = todoFileName;
    }
    //Read the entire todo list file
    FILE *todoFile = fopen(filePath, "w");
    if (!todoFile) {
        setError("Unable to open the todo file %s for writing.\nInternal error: %s", filePath, strerror(errno));
        return E_TODOSTORAGE_ERROR;
    }
    
    int retVal = E_TODOSTORAGE_SUCCESS;
    char *jsonStringToSave = createJSONStringFromTodos(todos);
    size_t jsonStringToSaveLen = strlen(jsonStringToSave);
    if (fwrite(jsonStringToSave, sizeof(char), strlen(jsonStringToSave), todoFile) != jsonStringToSaveLen) {
        setError("Unable to write all the bytes on the the todo file %s.\nInternal error: %s", filePath, strerror(errno));
        retVal = E_TODOSTORAGE_ERROR;
    }
    fclose(todoFile);
    free(jsonStringToSave);
    return retVal;
}

char *createJSONStringFromTodos(const todoList *todos)
{
    struct json_object *jsonObj = json_object_new_array();
    if (todos != NULL && todos->list != NULL) {
        for(size_t i = 0; i < todos->length; i++) {
            struct json_object *todoJSONItem = json_object_new_object();
            json_object_object_add(todoJSONItem, "name", json_object_new_string(todos->list[i].name));
            json_object_array_add(jsonObj, todoJSONItem);
        }
    }
    const char *jsonString = json_object_to_json_string(jsonObj);
    char *retVal = malloc(sizeof(char) * (strlen(jsonString) + 1));
    strcpy(retVal, jsonString);
    json_object_put(jsonObj);
    return retVal;
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
    char fileContent[DEFAULTCONFIGFILEMAXSIZE];
    sprintf(fileContent, "# Console todos config file\n\n\
todosFilePath = %s/todos.json\n", configDirectory);
    if (fputs(fileContent, configFile) < 0) {
        fclose(configFile);
        return E_TODOSTORAGE_ERROR;
    }
    
    fclose(configFile);
    return E_TODOSTORAGE_SUCCESS;
}
