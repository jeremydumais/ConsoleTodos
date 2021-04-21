#ifndef TODOLIST_H
#define TODOLIST_H

#include "todo.h"

typedef struct {
    todo *list;
    size_t length;
    unsigned int lastRuntimeId;
} todoList;

/**
 * @brief Add a new todo at the end of the list
 * 
 * @param todos the pointer of the todo list. 
 * @param item the pointer of the todo to append in the list. 
 * @return On success the function return 0, otherwise it return -1 
 */
int appendTodo(todoList *todos, todo *item);

/**
 * @brief Free a todo allocated object.
 * 
 * @param todos the pointer of the todo list.
 */
void freeTodoList(todoList *todos);

#endif