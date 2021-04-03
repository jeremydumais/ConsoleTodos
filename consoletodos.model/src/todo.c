#include "todo.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

int createTodo(todo *todoItem, const char *name)
{
    todoItem->name = NULL;
    todoItem->description = NULL;
    todoItem->priority = 3;
    if (name == NULL || strlen(name) == 0) {
        return -1;
    }
    size_t titleLength = strlen(name);
    todoItem->name = malloc(sizeof(char) * (titleLength + 1));
    strcpy(todoItem->name, name);
    return 0;
}

void freeTodoList(todo **list, size_t *listLength) 
{
    for(size_t i = 0; i < (*listLength); i++) {
        free((*list)[i].name);
    }
    free((*list));
    (*list) = NULL;
}
