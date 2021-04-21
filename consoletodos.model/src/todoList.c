#include "todoList.h"
#include <stdlib.h>

int appendTodo(todoList *todos, todo *item) 
{
    if (todos == NULL) {
        return -1;
    }
    if (todos->list == NULL) {
        todos->list = malloc(sizeof(todo));
    }
    else {
        todos->list = realloc(todos->list, sizeof(todo) * (todos->length + 1));
    }
    todos->length++;
    //Clone the todo in the newly memory space created

    //todos->lastRuntimeId++;

    return 0;
}

void freeTodoList(todoList *todos) 
{
    for(size_t i = 0; i < todos->length; i++) {
        free(todos->list[i].name);
    }
    free(todos->list);
    todos->list = NULL;
    todos->length = 0;

    todos->lastRuntimeId = 0;
}
