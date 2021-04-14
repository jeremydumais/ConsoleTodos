#include "todoList.h"
#include <stdlib.h>

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
