#ifndef TODOSTORAGE_H
#define TODOSTORAGE_H

#include "todo.h"
#include <stdbool.h>

/**
 * @brief The possible result value for the different storage functions.
 * The possible values are :
 *   E_TODOSTORAGE_SUCCESS
 *   E_TODOSTORAGE_ERROR
 */
enum _todo_storage_error
{
    E_TODOSTORAGE_SUCCESS = 0,
    E_TODOSTORAGE_ERROR = -1
};

/**
 * @brief Initialize the storage. This function initialize all the objects
 * needed to be able to load and save todos.
 * 
 * The function open the configuration file to retreive the todos 
 * configured file name.
 * 
 * @return On success the function return E_TODOSTORAGE_SUCCESS, otherwise
 * it return E_TODOSTORAGE_ERROR
 */
int initializeStorage();

/**
 * @brief Load the todos from the todos stored file.
 * 
 * @param filePath the filename including the full path where the todos are stored
 * @param list the pointer of the todo list
 * @param listLength the pointer of the list length
 * @return On success the function return E_TODOSTORAGE_SUCCESS, otherwise
 * it return E_TODOSTORAGE_ERROR
 */
int loadTodos(const char *filePath, todo **list, size_t *listLength);

/**
 * @brief Save the todos to the todos stored file.
 * 
 * @param filePath the filename including the full path where the todos are stored
 * @param list the pointer of the todo list
 * @param listLength the pointer of the list length
 * @return On success the function return E_TODOSTORAGE_SUCCESS, otherwise
 * it return E_TODOSTORAGE_ERROR 
 */
int saveTodos(const char *filePath, const todo *list, size_t listLength);

/**
 * @brief Create a new config file. This function is useful when no 
 * configuration file exist.
 * 
 * @param filePath the filename including full path where the new configuration
 * file will be store
 * @param configDirectory the configuration directory path where the todo file
 * will be store
 * @return On success the function return E_TODOSTORAGE_SUCCESS, otherwise
 * it return E_TODOSTORAGE_ERROR
 */
int createNewConfigFile(const char *filePath, const char *configDirectory);

#endif
