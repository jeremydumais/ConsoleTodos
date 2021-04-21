#include "main.h"
#include "todoTest.h"
#include "todo.h"
#include "unity.h"
#include <stdlib.h>
#include <string.h>

void runTodoTests()
{
    RUN_TEST(createTodo_WithNullName_ReturnNULL);
    RUN_TEST(createTodo_WithEmptyName_ReturnNULL);
    RUN_TEST(createTodo_WithWhiteSpaceName_ReturnNULL);
    RUN_TEST(createTodo_WithOneCharName_ReturnSuccess);

    RUN_TEST(updateTodo_WithNullTodo_ReturnMinus1);
    RUN_TEST(updateTodo_WithNullName_ReturnMinus1);
    RUN_TEST(updateTodo_WithEmptyName_ReturnMinus1);
    RUN_TEST(updateTodo_WithWhiteSpaceName_ReturnMinus1);
    RUN_TEST(updateTodo_WithValidDifferentName_Return0);
    RUN_TEST(updateTodo_WithValidSameName_Return0);
    
    RUN_TEST(freeTodo_WithNullTodo_ReturnSuccess);
    RUN_TEST(freeTodo_WithNonNullTodo_ReturnSuccess);

    RUN_TEST(freeTodoContent_WithNullTodo_ReturnSuccess);

    RUN_TEST(cloneTodo_WithValidSrcAndOnlyName_DoNothing);
}

void createTodo_WithNullName_ReturnNULL() 
{
    TEST_ASSERT_NULL(createTodo(NULL));
}

void createTodo_WithEmptyName_ReturnNULL() 
{
    TEST_ASSERT_NULL(createTodo(""));
}

void createTodo_WithWhiteSpaceName_ReturnNULL() 
{
    TEST_ASSERT_NULL(createTodo("     "));
}

void createTodo_WithOneCharName_ReturnSuccess() 
{
    todo *item = createTodo("a");
    TEST_ASSERT_NOT_NULL(item);
    freeTodo(&item);
}

void updateTodo_WithNullTodo_ReturnMinus1() 
{
    TEST_ASSERT_EQUAL_INT(-1, updateTodo(NULL, "a"));
}

void updateTodo_WithNullName_ReturnMinus1() 
{
    TEST_ASSERT_EQUAL_INT(-1, updateTodo(todoSample1, NULL));
}

void updateTodo_WithEmptyName_ReturnMinus1() 
{
    TEST_ASSERT_EQUAL_INT(-1, updateTodo(todoSample1, ""));
}

void updateTodo_WithWhiteSpaceName_ReturnMinus1() 
{
    TEST_ASSERT_EQUAL_INT(-1, updateTodo(todoSample1, "     "));
}

void updateTodo_WithValidDifferentName_Return0() 
{
    TEST_ASSERT_EQUAL_INT(0, updateTodo(todoSample1, "new name"));
    TEST_ASSERT_EQUAL_STRING("new name", todoSample1->name);
}

void updateTodo_WithValidSameName_Return0() 
{
    TEST_ASSERT_EQUAL_INT(0, updateTodo(todoSample1, "test"));
    TEST_ASSERT_EQUAL_STRING("test", todoSample1->name);
}

void freeTodo_WithNullTodo_ReturnSuccess() 
{
    freeTodo(NULL);
}

void freeTodo_WithNonNullTodo_ReturnSuccess() 
{
    freeTodo(&todoSample1);
    TEST_ASSERT_NULL(todoSample1);
}

void freeTodoContent_WithNullTodo_ReturnSuccess() 
{
    freeTodoContent(todoSample1);
    TEST_ASSERT_NOT_NULL(todoSample1);
    TEST_ASSERT_NULL(todoSample1->name);
    TEST_ASSERT_NULL(todoSample1->description);
    TEST_ASSERT_EQUAL_UINT(0, todoSample1->runtimeId);
    TEST_ASSERT_EQUAL_INT(3, todoSample1->priority);
    TEST_ASSERT_EQUAL_INT(0, todoSample1->datetime);
}

void cloneTodo_WithValidSrcAndOnlyName_DoNothing() 
{
    todo dst;
    cloneTodo(todoSample1, &dst);
    TEST_ASSERT_EQUAL_STRING(todoSample1->name, dst.name);
    TEST_ASSERT_NULL(dst.description);
    TEST_ASSERT_EQUAL_UINT(todoSample1->runtimeId, dst.runtimeId);
    TEST_ASSERT_EQUAL_INT(todoSample1->priority, dst.priority);
    TEST_ASSERT_EQUAL_INT(todoSample1->datetime, dst.datetime);
}
