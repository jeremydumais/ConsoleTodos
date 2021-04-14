#include "todoList.h"
#include <stdlib.h>

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
