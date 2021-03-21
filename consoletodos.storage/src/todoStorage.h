#ifndef TODOSTORAGE_H
#define TODOSTORAGE_H

#include "linux/limits.h"
#include "todo.h"
#include <stdbool.h>

#define STORAGEERRORMSG_MAXLEN PATH_MAX + 1024

static char todoFileName[PATH_MAX - 1];
static char configDirectory[PATH_MAX - 1];
static char configFilePath[PATH_MAX - 1];
static char lastStorageError[STORAGEERRORMSG_MAXLEN];

static enum _storage_error {
    E_STORAGESUCCESS = 0,
    E_STORAGECONFIGDIRCREATEDENIED = -1,
    E_STORAGECONFIGFILECREATEERROR = -2
};

int initializeStorage();
int loadTodos(const char *filePath, todo **list, int *listLength);
int saveTodos(todo **list, int listLength);
const char *getLastStorageError();
const char *getStorageTodoFileName();
bool _directoryExist(const char *folderPath);
bool _fileExist(const char *filePath);
int createNewConfigFile(const char *filePath, const char *configDirectory);

#endif
