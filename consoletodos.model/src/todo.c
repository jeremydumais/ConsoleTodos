#include "todo.h"
#include "typeUtil.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static unsigned int lastAssignedRuntimeId = 0;

int createTodo(todo *todoItem, const char *name)
{
    if (todoItem == NULL || isStringEmptyOrWhiteSpace(name)) {
        return -1;
    }
    todoItem->runtimeId = 0;
    todoItem->name = NULL;
    todoItem->description = NULL;
    todoItem->priority = 3;
    
    size_t titleLength = strlen(name);
    todoItem->name = malloc(sizeof(char) * (titleLength + 1));
    strcpy(todoItem->name, name);
    //Assign a realtime id 
    todoItem->runtimeId = ++lastAssignedRuntimeId;
    return 0;
}

int updateTodo(todo *todoItem, const char *name) 
{
    if (todoItem == NULL || isStringEmptyOrWhiteSpace(name)) {
        return -1;
    }
    if (strcmp(todoItem->name, name) != 0) {
        free(todoItem->name);
        todoItem->name = malloc(sizeof(char) * (strlen(name) + 1));
        strcpy(todoItem->name, name);
    }
    return 0;
}

void freeTodoList(todo **list, size_t *listLength) 
{
    for(size_t i = 0; i < (*listLength); i++) {
        free((*list)[i].name);
    }
    free((*list));
    (*list) = NULL;
    (*listLength) = 0;

    lastAssignedRuntimeId = 0;
}
