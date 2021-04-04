#include "todoStorageTest.h"
#include "todo.h"
#include "unity.h"
#include <stdlib.h>

extern void createTodosFromJSONString(const char *fileContent, todo **list, size_t *listLength);
extern char *createJSONStringFromTodos(const todo *list, size_t listLength);

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

void createTodosFromJSONString_WithNullStr_ReturnZeroTodo() 
{
    todo *list = NULL;
    size_t length = 0;
    createTodosFromJSONString(NULL, &list, &length);
    TEST_ASSERT_NULL(list);
    TEST_ASSERT_EQUAL_size_t(0, length);
}

void createTodosFromJSONString_WithEmptyStr_ReturnZeroTodo() 
{
    todo *list = NULL;
    size_t length = 0;
    createTodosFromJSONString("", &list, &length);
    TEST_ASSERT_NULL(list);
    TEST_ASSERT_EQUAL_size_t(0, length);
}

void createTodosFromJSONString_WithWhiteSpacesStr_ReturnZeroTodo()
{
    todo *list = NULL;
    size_t length = 0;
    createTodosFromJSONString("           ", &list, &length);
    TEST_ASSERT_NULL(list);
    TEST_ASSERT_EQUAL_size_t(0, length);
}

void createTodosFromJSONString_WithNotArrayStr_ReturnZeroTodo() 
{
    todo *list = NULL;
    size_t length = 0;
    createTodosFromJSONString("{}", &list, &length);
    TEST_ASSERT_NULL(list);
    TEST_ASSERT_EQUAL_size_t(0, length);
}

void createTodosFromJSONString_WithEmptyArrayStr_ReturnZeroTodo() 
{
    todo *list = NULL;
    size_t length = 0;
    createTodosFromJSONString("[]", &list, &length);
    TEST_ASSERT_NULL(list);
    TEST_ASSERT_EQUAL_size_t(0, length);
    free(list);
}

void createTodosFromJSONString_WithOneTodoOnlyNameStr_ReturnOneTodo() 
{
    todo *list = NULL;
    size_t length = 0;
    createTodosFromJSONString("[ { \"name\": \"test\" } ]", &list, &length);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_size_t(1, length);
    TEST_ASSERT_EQUAL_STRING("test", list[0].name);
    free(list[0].name);
    free(list);
}

void createTodosFromJSONString_WithTwoTodosOnlyNameStr_ReturnTwoTodos() 
{
    todo *list = NULL;
    size_t length = 0;
    createTodosFromJSONString("[ { \"name\": \"test\" }, { \"name\": \"test2\" } ]", &list, &length);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_size_t(2, length);
    TEST_ASSERT_EQUAL_STRING("test", list[0].name);
    TEST_ASSERT_EQUAL_STRING("test2", list[1].name);
    free(list[0].name);
    free(list[1].name);
    free(list);
}

void createJSONStringFromTodos_WithNullList_ReturnEmptyJSONArray() 
{
    todo *list = NULL;
    char *actual = createJSONStringFromTodos(list, 0);
    TEST_ASSERT_EQUAL_STRING("[ ]", actual);
    free(actual);

}

void createJSONStringFromTodos_WithListOneTodoOnlyName_ReturnJSONArrayOneItem() 
{
    todo list[1];
    list[0].name = malloc(sizeof(char) * 5);
    strcpy(list[0].name, "test");
    char *actual = createJSONStringFromTodos(list, 1);
    TEST_ASSERT_EQUAL_STRING("[ { \"name\": \"test\" } ]", actual);
    free(list[0].name);
    free(actual);
}

void createJSONStringFromTodos_WithListTwoTodosOnlyName_ReturnJSONArrayTwoItems() 
{
    todo list[2];
    list[0].name = malloc(sizeof(char) * 5);
    strcpy(list[0].name, "test");
    list[1].name = malloc(sizeof(char) * 6);
    strcpy(list[1].name, "test2");
    char *actual = createJSONStringFromTodos(list, 2);
    TEST_ASSERT_EQUAL_STRING("[ { \"name\": \"test\" }, { \"name\": \"test2\" } ]", actual);
    free(list[0].name);
    free(list[1].name);
    free(actual);
}
