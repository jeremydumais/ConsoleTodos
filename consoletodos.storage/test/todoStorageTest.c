#include "todoStorageTest.h"
#include "todo.h"
#include "todoList.h"
#include "unity.h"
#include <stdlib.h>
#include <string.h>

extern void createTodosFromJSONString(const char *fileContent, todoList *todos);
extern char *createJSONStringFromTodos(const todoList *todos);
todoList getNewEmptyTodoList();
todoList getNewTodoList(size_t nbOfTodos);

void runTodoStorageTests() 
{
    RUN_TEST(createTodosFromJSONString_WithNullStr_ReturnZeroTodo);
    RUN_TEST(createTodosFromJSONString_WithEmptyStr_ReturnZeroTodo);
    RUN_TEST(createTodosFromJSONString_WithWhiteSpacesStr_ReturnZeroTodo);
    RUN_TEST(createTodosFromJSONString_WithNotArrayStr_ReturnZeroTodo);
    RUN_TEST(createTodosFromJSONString_WithEmptyArrayStr_ReturnZeroTodo);
    RUN_TEST(createTodosFromJSONString_WithOneTodoOnlyNameStr_ReturnOneTodo);
    RUN_TEST(createTodosFromJSONString_WithTwoTodosOnlyNameStr_ReturnTwoTodos);

    RUN_TEST(createJSONStringFromTodos_WithNullList_ReturnEmptyJSONArray);
    RUN_TEST(createJSONStringFromTodos_WithListOneTodoOnlyName_ReturnJSONArrayOneItem);
    RUN_TEST(createJSONStringFromTodos_WithListTwoTodosOnlyName_ReturnJSONArrayTwoItems);
}

todoList getNewEmptyTodoList()
{
    todoList todos;
    todos.list = NULL;
    todos.length = 0;
    todos.lastRuntimeId = 0;
    return todos;
}

todoList getNewTodoList(size_t nbOfTodos) 
{
    todoList todos;
    todos.list = malloc(sizeof(todo) * nbOfTodos);
    todos.length = nbOfTodos;
    todos.lastRuntimeId = 0;
    return todos;
}


void createTodosFromJSONString_WithNullStr_ReturnZeroTodo() 
{
    todoList todos = getNewEmptyTodoList();
    createTodosFromJSONString(NULL, &todos);
    TEST_ASSERT_NULL(todos.list);
    TEST_ASSERT_EQUAL_size_t(0, todos.length);
}

void createTodosFromJSONString_WithEmptyStr_ReturnZeroTodo() 
{
    todoList todos = getNewEmptyTodoList();
    createTodosFromJSONString("", &todos);
    TEST_ASSERT_NULL(todos.list);
    TEST_ASSERT_EQUAL_size_t(0, todos.length);
}

void createTodosFromJSONString_WithWhiteSpacesStr_ReturnZeroTodo()
{
    todoList todos = getNewEmptyTodoList();
    createTodosFromJSONString("           ", &todos);
    TEST_ASSERT_NULL(todos.list);
    TEST_ASSERT_EQUAL_size_t(0, todos.length);
}

void createTodosFromJSONString_WithNotArrayStr_ReturnZeroTodo() 
{
    todoList todos = getNewEmptyTodoList();
    createTodosFromJSONString("{}", &todos);
    TEST_ASSERT_NULL(todos.list);
    TEST_ASSERT_EQUAL_size_t(0, todos.length);
}

void createTodosFromJSONString_WithEmptyArrayStr_ReturnZeroTodo() 
{
    todoList todos = getNewEmptyTodoList();
    createTodosFromJSONString("[]", &todos);
    TEST_ASSERT_NULL(todos.list);
    TEST_ASSERT_EQUAL_size_t(0, todos.length);
    freeTodoList(&todos);
}

void createTodosFromJSONString_WithOneTodoOnlyNameStr_ReturnOneTodo() 
{
    todoList todos = getNewEmptyTodoList();
    createTodosFromJSONString("[ { \"name\": \"test\" } ]", &todos);
    TEST_ASSERT_NOT_NULL(todos.list);
    TEST_ASSERT_EQUAL_size_t(1, todos.length);
    TEST_ASSERT_EQUAL_STRING("test", todos.list[0].name);
    freeTodoList(&todos);
}

void createTodosFromJSONString_WithTwoTodosOnlyNameStr_ReturnTwoTodos() 
{
    todoList todos = getNewEmptyTodoList();
    createTodosFromJSONString("[ { \"name\": \"test\" }, { \"name\": \"test2\" } ]", &todos);
    TEST_ASSERT_NOT_NULL(todos.list);
    TEST_ASSERT_EQUAL_size_t(2, todos.length);
    TEST_ASSERT_EQUAL_STRING("test", todos.list[0].name);
    TEST_ASSERT_EQUAL_STRING("test2", todos.list[1].name);
    freeTodoList(&todos);

}

void createJSONStringFromTodos_WithNullList_ReturnEmptyJSONArray() 
{
    char *actual = createJSONStringFromTodos(NULL);
    TEST_ASSERT_EQUAL_STRING("[ ]", actual);
    free(actual);

}

void createJSONStringFromTodos_WithListOneTodoOnlyName_ReturnJSONArrayOneItem() 
{
    todoList todos = getNewTodoList(1);
    todos.list[0].name = malloc(sizeof(char) * 5);
    strcpy(todos.list[0].name, "test");
    char *actual = createJSONStringFromTodos(&todos);
    TEST_ASSERT_EQUAL_STRING("[ { \"name\": \"test\" } ]", actual);
    freeTodoList(&todos);
    free(actual);
}

void createJSONStringFromTodos_WithListTwoTodosOnlyName_ReturnJSONArrayTwoItems() 
{
    todoList todos = getNewTodoList(2);
    todos.list[0].name = malloc(sizeof(char) * 5);
    strcpy(todos.list[0].name, "test");
    todos.list[1].name = malloc(sizeof(char) * 6);
    strcpy(todos.list[1].name, "test2");
    char *actual = createJSONStringFromTodos(&todos);
    TEST_ASSERT_EQUAL_STRING("[ { \"name\": \"test\" }, { \"name\": \"test2\" } ]", actual);
    freeTodoList(&todos);
    free(actual);
}
