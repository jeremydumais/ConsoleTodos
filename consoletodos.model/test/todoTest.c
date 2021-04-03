#include "todoTest.h"
#include "todo.h"
#include "unity.h"

void runTodoTests()
{
    RUN_TEST(createTodo_WithNullName_ReturnMinus1);
    RUN_TEST(createTodo_WithEmptyName_ReturnMinus1);
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