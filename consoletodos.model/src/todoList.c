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
    //Clone the todo in the newly memory space created
    if (cloneTodo(item, todos->list + todos->length) != 0) {
        return -1;
    }
    todos->list[todos->length].runtimeId = ++(todos->lastRuntimeId);
    todos->length++;

    return 0;
}

void freeTodoList(todoList *todos) 
{
    for(size_t i = 0; i < todos->length; i++) {
        freeTodoContent(todos->list + i);
    }
    free(todos->list);
    todos->list = NULL;
    todos->length = 0;

    todos->lastRuntimeId = 0;
}
