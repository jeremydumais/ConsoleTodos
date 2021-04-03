#include "todoTest.h"
#include "todo.h"
#include "unity.h"

void runTodoTests()
{
    RUN_TEST(createTodo_WithNullName_ReturnMinus1);
    RUN_TEST(createTodo_WithEmptyName_ReturnMinus1);
    RUN_TEST(createTodo_WithWhiteSpaceName_ReturnMinus1);
    RUN_TEST(createTodo_WithOneCharName_Return0);
}

void createTodo_WithNullName_ReturnMinus1() 
{
    todo item;
    TEST_ASSERT_EQUAL_INT(-1, createTodo(&item, NULL));
}

void createTodo_WithEmptyName_ReturnMinus1() 
{
    todo item;
    TEST_ASSERT_EQUAL_INT(-1, createTodo(&item, ""));
}

void createTodo_WithWhiteSpaceName_ReturnMinus1() 
{
    todo item;
    TEST_ASSERT_EQUAL_INT(-1, createTodo(&item, "     "));
}

void createTodo_WithOneCharName_Return0() 
{
    todo item;
    TEST_ASSERT_EQUAL_INT(0, createTodo(&item, "a"));
}