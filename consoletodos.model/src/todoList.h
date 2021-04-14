#ifndef TODOLIST_H
#define TODOLIST_H

#include "todo.h"

typedef struct {
    todo *list;
    size_t length;
    unsigned int lastRuntimeId;
} todoList;

/**
 * @brief Free a todo allocated object.
 * 
 * @param list the pointer of the todo list.
 * @param listLength the pointer of the todo list length.
 */
void freeTodoList(todoList *todos);

#endif