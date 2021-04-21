#include "todo.h"
#include "typeUtil.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

todo *createTodo(const char *name)
{
    if (isStringEmptyOrWhiteSpace(name)) {
        return NULL;
    }
    todo *todoItem = malloc(sizeof(todo));
    todoItem->runtimeId = 0;
    todoItem->name = NULL;
    todoItem->description = NULL;
    todoItem->priority = 3;
    
    size_t titleLength = strlen(name);
    todoItem->name = malloc(sizeof(char) * (titleLength + 1));
    strcpy(todoItem->name, name);
    return todoItem;
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

void freeTodo(todo **todoItem) 
{
    if (todoItem != NULL && *todoItem != NULL) {
        freeTodoContent(*todoItem);
        free(*todoItem);
        *todoItem = NULL;
    }
}

void freeTodoContent(todo *todoItem) 
{
    if (todoItem != NULL) {
        if (todoItem->name != NULL) {
            free(todoItem->name);
            todoItem->name = NULL;
        }
        if (todoItem->description != NULL) {
            free(todoItem->description);
            todoItem->description = NULL;
        }
        todoItem->runtimeId = 0;
        todoItem->priority = 3;
        todoItem->datetime = 0;
    }
}

void cloneTodo(todo *src, todo *dst) 
{
    if (src->name != NULL) {
        dst->name = malloc(sizeof(char) * (strlen(src->name) + 1));
        strcpy(dst->name, src->name);
    }
    else {
        dst->name = NULL;
    }
    if (src->description != NULL) {
        dst->description = malloc(sizeof(char) * (strlen(src->description) + 1));
        strcpy(dst->description, src->description);
    }
    else {
        dst->description = NULL;
    }
    dst->priority = src->priority;
    dst->runtimeId = src->runtimeId;
    dst->datetime = src->datetime;
}
