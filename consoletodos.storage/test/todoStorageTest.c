#include "todoStorageTest.h"
#include "todo.h"
#include "todoList.h"
#include "errStorage.h"
#include "unity.h"
#include <stdlib.h>
#include <string.h>

extern bool createTodosFromJSONString(const char *fileContent, todoList *todos);
extern char *createJSONStringFromTodos(const todoList *todos);
todoList *getNewEmptyTodoList();
todoList *getNewTodoList(size_t nbOfTodos);

void runTodoStorageTests() 
{
    RUN_TEST(createTodosFromJSONString_WithNullStr_ReturnFalse);
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

todoList *getNewEmptyTodoList()
{
    todoList *todos = malloc(sizeof(todoList));
    todos->list = NULL;
    todos->length = 0;
    todos->lastRuntimeId = 0;
    return todos;
}

todoList *getNewTodoList(size_t nbOfTodos) 
{
    todoList *todos = malloc(sizeof(todoList));

    todos->list = NULL;
    todos->length = 0;
    todos->lastRuntimeId = 0;

    for(int i = 0; i < nbOfTodos; i++) {
        char title[7];
        sprintf(title, "test%d", i+1);
        todo *item = createTodo(title);
        appendTodo(todos, item);
        freeTodo(&item);
    }
    return todos;
}


void createTodosFromJSONString_WithNullStr_ReturnFalse() 
{
    todoList *todos = getNewEmptyTodoList();
    setError("");
    TEST_ASSERT_FALSE(createTodosFromJSONString(NULL, todos));
    TEST_ASSERT_EQUAL_STRING("The file content is null", getLastStorageError());
    TEST_ASSERT_NULL(todos->list);
    TEST_ASSERT_EQUAL_size_t(0, todos->length);
    free(todos);
}

void createTodosFromJSONString_WithEmptyStr_ReturnZeroTodo() 
{
    todoList *todos = getNewEmptyTodoList();
    setError("");
    TEST_ASSERT_FALSE(createTodosFromJSONString("", todos));
    TEST_ASSERT_EQUAL_STRING("The file content is not a json array", getLastStorageError());
    TEST_ASSERT_NULL(todos->list);
    TEST_ASSERT_EQUAL_size_t(0, todos->length);
    free(todos);
}

void createTodosFromJSONString_WithWhiteSpacesStr_ReturnZeroTodo()
{
    todoList *todos = getNewEmptyTodoList();
    setError("");
    createTodosFromJSONString("           ", todos);
    TEST_ASSERT_NULL(todos->list);
    TEST_ASSERT_EQUAL_size_t(0, todos->length);
    free(todos);
}

void createTodosFromJSONString_WithNotArrayStr_ReturnZeroTodo() 
{
    todoList *todos = getNewEmptyTodoList();
    setError("");
    createTodosFromJSONString("{}", todos);
    TEST_ASSERT_NULL(todos->list);
    TEST_ASSERT_EQUAL_size_t(0, todos->length);
    free(todos);
}

void createTodosFromJSONString_WithEmptyArrayStr_ReturnZeroTodo() 
{
    todoList *todos = getNewEmptyTodoList();
    setError("");
    createTodosFromJSONString("[]", todos);
    TEST_ASSERT_NULL(todos->list);
    TEST_ASSERT_EQUAL_size_t(0, todos->length);
    freeTodoList(todos);
    free(todos);
}

void createTodosFromJSONString_WithOneTodoOnlyNameStr_ReturnOneTodo() 
{
    todoList *todos = getNewEmptyTodoList();
    setError("");
    TEST_ASSERT_TRUE(createTodosFromJSONString("[ { \"name\": \"test\" } ]", todos));
    TEST_ASSERT_NOT_NULL(todos->list);
    TEST_ASSERT_EQUAL_size_t(1, todos->length);
    TEST_ASSERT_EQUAL_STRING("test", todos->list[0].name);
    freeTodoList(todos);
    free(todos);
}

void createTodosFromJSONString_WithTwoTodosOnlyNameStr_ReturnTwoTodos() 
{
    todoList *todos = getNewEmptyTodoList();
    setError("");
    TEST_ASSERT_TRUE(createTodosFromJSONString("[ { \"name\": \"test\" }, { \"name\": \"test2\" } ]", todos));
    TEST_ASSERT_NOT_NULL(todos->list);
    TEST_ASSERT_EQUAL_size_t(2, todos->length);
    TEST_ASSERT_EQUAL_STRING("test", todos->list[0].name);
    TEST_ASSERT_EQUAL_STRING("test2", todos->list[1].name);
    freeTodoList(todos);
    free(todos);
}

void createJSONStringFromTodos_WithNullList_ReturnEmptyJSONArray() 
{
    char *actual = createJSONStringFromTodos(NULL);
    TEST_ASSERT_EQUAL_STRING("[ ]", actual);
    free(actual);

}

void createJSONStringFromTodos_WithListOneTodoOnlyName_ReturnJSONArrayOneItem() 
{
    todoList *todos = getNewTodoList(1);
    char *actual = createJSONStringFromTodos(todos);
    TEST_ASSERT_EQUAL_STRING("[ { \"name\": \"test1\" } ]", actual);
    freeTodoList(todos);
    free(todos);
    free(actual);
}

void createJSONStringFromTodos_WithListTwoTodosOnlyName_ReturnJSONArrayTwoItems() 
{
    todoList *todos = getNewTodoList(2);
    char *actual = createJSONStringFromTodos(todos);
    TEST_ASSERT_EQUAL_STRING("[ { \"name\": \"test1\" }, { \"name\": \"test2\" } ]", actual);
    freeTodoList(todos);
    free(todos);
    free(actual);
}
