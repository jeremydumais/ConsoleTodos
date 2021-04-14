#ifndef TODO_H
#define TODO_H

#include <time.h>

#define NAMESIZE 128
#define DESCRSIZE 512

typedef struct {
    unsigned int runtimeId;
    char *name;
    char *description;
    time_t datetime;
    int priority;
} todo;

extern unsigned int lastAssignedRuntimeId;

/**
 * @brief Create a new todo object. The caller is responsible to free the object
 * once it's not needed anymore.
 * 
 * @param name the name (title) of the todo
 * @return On success return 0, otherwise return -1
 */
int createTodo(todo *todoItem, const char *name);

/**
 * @brief Update and existing todo item. 
 * 
 * @param todoItem 
 * @param name the new name (title) of the todo
 * @return On success return 0, otherwise return -1
 */
int updateTodo(todo *todoItem, const char *name);

#endif