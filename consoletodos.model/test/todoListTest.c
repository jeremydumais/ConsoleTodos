#include "main.h"
#include "todoListTest.h"
#include "todoList.h"
#include <unity.h>

void runTodoListTests() 
{
    RUN_TEST(appendTodo_WithNullTodos_ReturnMinus1);
    RUN_TEST(appendTodo_WithEmptyTodos_Return0);
    RUN_TEST(appendTodo_WithNullItem_ReturnMinus1);
    RUN_TEST(appendTodo_ToAOneListItem_ReturnMinus0);
}

void appendTodo_WithNullTodos_ReturnMinus1() 
{
    TEST_ASSERT_EQUAL_INT(-1, appendTodo(NULL, todoSample1));
}

void appendTodo_WithEmptyTodos_Return0() 
{
    TEST_ASSERT_NULL(emptyTodoList.list);
    TEST_ASSERT_EQUAL_INT(0, emptyTodoList.lastRuntimeId);
    TEST_ASSERT_EQUAL_INT(0, appendTodo(&emptyTodoList, todoSample1));
    TEST_ASSERT_NOT_NULL(emptyTodoList.list);
    TEST_ASSERT_EQUAL_INT(1, emptyTodoList.length);
    TEST_ASSERT_EQUAL_INT(1, emptyTodoList.lastRuntimeId);
    todoSample1->runtimeId = 1;
    TEST_ASSERT_TRUE(isTodoEqual(emptyTodoList.list + 0, todoSample1));
}

void appendTodo_WithNullItem_ReturnMinus1() 
{
    TEST_ASSERT_EQUAL_INT(-1, appendTodo(&emptyTodoList, NULL));
}

void appendTodo_ToAOneListItem_ReturnMinus0()
{
    TEST_ASSERT_EQUAL_INT(1, oneItemTodoList.lastRuntimeId);
    TEST_ASSERT_EQUAL_INT(0, appendTodo(&oneItemTodoList, todoSample1));
    TEST_ASSERT_NOT_NULL(oneItemTodoList.list);
    TEST_ASSERT_EQUAL_INT(2, oneItemTodoList.length);
    TEST_ASSERT_EQUAL_INT(2, oneItemTodoList.lastRuntimeId);
    todoSample2->runtimeId = 1;
    todoSample1->runtimeId = 2;
    TEST_ASSERT_TRUE(isTodoEqual(oneItemTodoList.list + 0, todoSample2));
    TEST_ASSERT_TRUE(isTodoEqual(oneItemTodoList.list + 1, todoSample1));
}