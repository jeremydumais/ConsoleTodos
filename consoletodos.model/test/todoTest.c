#include "todoTest.h"
#include "todo.h"
#include "unity.h"
#include <stdlib.h>
#include <string.h>

void runTodoTests()
{
    RUN_TEST(createTodo_WithNullTodo_ReturnMinus1);
    RUN_TEST(createTodo_WithNullName_ReturnMinus1);
    RUN_TEST(createTodo_WithEmptyName_ReturnMinus1);
    RUN_TEST(createTodo_WithWhiteSpaceName_ReturnMinus1);
    RUN_TEST(createTodo_WithOneCharName_Return0);

    RUN_TEST(updateTodo_WithNullTodo_ReturnMinus1);
    RUN_TEST(updateTodo_WithNullName_ReturnMinus1);
    RUN_TEST(updateTodo_WithEmptyName_ReturnMinus1);
    RUN_TEST(updateTodo_WithWhiteSpaceName_ReturnMinus1);
    RUN_TEST(updateTodo_WithValidDifferentName_Return0);
    RUN_TEST(updateTodo_WithValidSameName_Return0);
}

void createTodo_WithNullTodo_ReturnMinus1() 
{
    unsigned int lastAssignedRuntimeId = 0;
    TEST_ASSERT_EQUAL_INT(-1, createTodo(NULL, "test", &lastAssignedRuntimeId));
}

void createTodo_WithNullName_ReturnMinus1() 
{
    todo item;
    unsigned int lastAssignedRuntimeId = 0;
    TEST_ASSERT_EQUAL_INT(-1, createTodo(&item, NULL, &lastAssignedRuntimeId));
}

void createTodo_WithEmptyName_ReturnMinus1() 
{
    todo item;
    unsigned int lastAssignedRuntimeId = 0;
    TEST_ASSERT_EQUAL_INT(-1, createTodo(&item, "", &lastAssignedRuntimeId));
}

void createTodo_WithWhiteSpaceName_ReturnMinus1() 
{
    todo item;
    unsigned int lastAssignedRuntimeId = 0;
    TEST_ASSERT_EQUAL_INT(-1, createTodo(&item, "     ", &lastAssignedRuntimeId));
}

void createTodo_WithOneCharName_Return0() 
{
    todo item;
    unsigned int lastAssignedRuntimeId = 0;
    TEST_ASSERT_EQUAL_INT(0, createTodo(&item, "a", &lastAssignedRuntimeId));
    free(item.name);
}

void updateTodo_WithNullTodo_ReturnMinus1() 
{
    TEST_ASSERT_EQUAL_INT(-1, updateTodo(NULL, "a"));
}

void updateTodo_WithNullName_ReturnMinus1() 
{
    todo item;
    TEST_ASSERT_EQUAL_INT(-1, updateTodo(&item, NULL));
}

void updateTodo_WithEmptyName_ReturnMinus1() 
{
    todo item;
    TEST_ASSERT_EQUAL_INT(-1, updateTodo(&item, ""));
}

void updateTodo_WithWhiteSpaceName_ReturnMinus1() 
{
    todo item;
    TEST_ASSERT_EQUAL_INT(-1, updateTodo(&item, "     "));
}

void updateTodo_WithValidDifferentName_Return0() 
{
    todo item;
    item.name = malloc(sizeof(char) * 5);
    strcpy(item.name, "test");
    TEST_ASSERT_EQUAL_INT(0, updateTodo(&item, "new name"));
    TEST_ASSERT_EQUAL_STRING("new name", item.name);
    free(item.name);
}

void updateTodo_WithValidSameName_Return0() 
{
    todo item;
    item.name = malloc(sizeof(char) * 5);
    strcpy(item.name, "test");
    TEST_ASSERT_EQUAL_INT(0, updateTodo(&item, "test"));
    TEST_ASSERT_EQUAL_STRING("test", item.name);
    free(item.name);
}