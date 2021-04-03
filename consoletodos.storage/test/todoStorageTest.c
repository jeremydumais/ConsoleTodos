#include "todoStorageTest.h"
#include "todo.h"
#include "unity.h"

extern void createTodosFromJSONString(const char *fileContent, todo **list, size_t *listLength);

void runTodoStorageTests() 
{
    RUN_TEST(createTodosFromJSONString_WithNullStr_ReturnZeroTodo);
    RUN_TEST(createTodosFromJSONString_WithEmptyStr_ReturnZeroTodo);
    RUN_TEST(createTodosFromJSONString_WithWhiteSpacesStr_ReturnZeroTodo);
    RUN_TEST(createTodosFromJSONString_WithNotArrayStr_ReturnZeroTodo);
    RUN_TEST(createTodosFromJSONString_WithEmptyArrayStr_ReturnZeroTodo);
    RUN_TEST(createTodosFromJSONString_WithOneTodoOnlyNameStr_ReturnOneTodo);
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
}

void createTodosFromJSONString_WithOneTodoOnlyNameStr_ReturnOneTodo() 
{
    todo *list = NULL;
    size_t length = 0;
    createTodosFromJSONString("[ { \"name\": \"test\" } ]", &list, &length);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_size_t(1, length);
    TEST_ASSERT_EQUAL_STRING("test", list[0].name);
}
