#ifndef TODOSTORAGE_H
#define TODOSTORAGE_H

#include "todo.h"
#include <stdbool.h>

enum _todo_storage_error {
    E_TODOSTORAGE_SUCCESS = 0,
    E_TODOSTORAGE_ERROR = -1
};

int initializeStorage();
int loadTodos(const char *filePath, todo **list, int *listLength);
//int saveTodos(todo **list, int listLength);
const char *getStorageTodoFileName();
int createNewConfigFile(const char *filePath, const char *configDirectory);

#endif
