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

/**
 * @brief Create a new todo object. The caller is responsible to free the object
 * once it's not needed anymore.
 * 
 * @param name the name (title) of the todo
 * @return On success return an pointer to an allocated todo, otherwise return NULL
 */
todo *createTodo(const char *name);

/**
 * @brief Update and existing todo item. 
 * 
 * @param todoItem 
 * @param name the new name (title) of the todo
 * @return On success return 0, otherwise return -1
 */
int updateTodo(todo *todoItem, const char *name);

/**
 * @brief Free the todo item and it's resources.
 * 
 * @param todoItem the todo item to free. This param can be NULL.
 */
void freeTodo(todo **todoItem);

/**
 * @brief Free the ressources of a todo item. 
 * This function free for example the name (char *) but now the todo struct memory.
 * 
 * @param todoItem the todo item to free. This param can be NULL.
 */
void freeTodoContent(todo *todoItem);

/**
 * @brief Copy all the values and memory from the 
 * src memory pointer to the dst memory pointer.
 * 
 * @param src the todo pointer item that act as the source
 * @param dst the todo pointer item that act as the destination
 */
void cloneTodo(todo *src, todo *dst);

#endif