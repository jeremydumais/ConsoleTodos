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

    RUN_TEST(cloneTodo_WithValidNullSrc_ReturnMinus1);
    RUN_TEST(cloneTodo_WithValidNullDst_ReturnMinus1);
    RUN_TEST(cloneTodo_WithValidSrcAndOnlyName_ReturnZero);

    RUN_TEST(isTodoEqual_WithNullFirstAndNotNullSecond_ReturnFalse);
    RUN_TEST(isTodoEqual_WithNullNotNullAndSecondNull_ReturnFalse);
    RUN_TEST(isTodoEqual_WithFirstAndSecondNull_ReturnTrue);
    RUN_TEST(isTodoEqual_WithFirstTodoNameNull_ReturnFalse);
    RUN_TEST(isTodoEqual_WithSecondTodoNameNull_ReturnFalse);
    RUN_TEST(isTodoEqual_WithFirstAndSecondTodoNameNull_ReturnTrue);
    RUN_TEST(isTodoEqual_WithSecondTodoNameDiff_ReturnFalse);
    RUN_TEST(isTodoEqual_WithSecondTodoRuntimeIdDiff_ReturnFalse);
    RUN_TEST(isTodoEqual_WithSecondTodoDescriptionDiff_ReturnFalse);
    RUN_TEST(isTodoEqual_WithFirstTodoDescriptionNull_ReturnFalse);
    RUN_TEST(isTodoEqual_WithSecondTodoDescriptionNull_ReturnFalse);
    RUN_TEST(isTodoEqual_WithFirstAndSecondTodoDescriptionNull_ReturnTrue);
    RUN_TEST(isTodoEqual_WithDateTimeDiff_ReturnFalse);
    RUN_TEST(isTodoEqual_WithRuntimeIdDiff_ReturnFalse);
    RUN_TEST(isTodoEqual_WithPriorityDiff_ReturnFalse);
    RUN_TEST(isTodoEqual_WithAllFieldIdentical_ReturnTrue);
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

void cloneTodo_WithValidNullSrc_ReturnMinus1()
{
    todo dst;
    TEST_ASSERT_EQUAL_INT(-1, cloneTodo(NULL, &dst));
}

void cloneTodo_WithValidNullDst_ReturnMinus1()
{
    TEST_ASSERT_EQUAL_INT(-1, cloneTodo(todoSample1, NULL));
}

void cloneTodo_WithValidSrcAndOnlyName_ReturnZero() 
{
    todo dst;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &dst));
    TEST_ASSERT_EQUAL_STRING(todoSample1->name, dst.name);
    TEST_ASSERT_NULL(dst.description);
    TEST_ASSERT_EQUAL_UINT(todoSample1->runtimeId, dst.runtimeId);
    TEST_ASSERT_EQUAL_INT(todoSample1->priority, dst.priority);
    TEST_ASSERT_EQUAL_INT(todoSample1->datetime, dst.datetime);
    freeTodoContent(&dst);
}

void isTodoEqual_WithNullFirstAndNotNullSecond_ReturnFalse()
{
    TEST_ASSERT_FALSE(isTodoEqual(NULL, todoSample1));
}

void isTodoEqual_WithNullNotNullAndSecondNull_ReturnFalse()
{
    TEST_ASSERT_FALSE(isTodoEqual(todoSample1, NULL));
}

void isTodoEqual_WithFirstAndSecondNull_ReturnTrue()
{
    TEST_ASSERT_TRUE(isTodoEqual(NULL, NULL));
}

void isTodoEqual_WithSecondTodoNameDiff_ReturnFalse()
{
    todo second;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &second));
    free(second.name);
    second.name = malloc(sizeof(char) * 5);
    strcpy(second.name, "test");
    TEST_ASSERT_FALSE(isTodoEqual(todoSample1, &second));
    freeTodoContent(&second);
}

void isTodoEqual_WithFirstTodoNameNull_ReturnFalse()
{
    todo second;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &second));
    free(todoSample1->name);
    todoSample1->name = NULL;
    TEST_ASSERT_FALSE(isTodoEqual(todoSample1, &second));
    freeTodoContent(&second);
}

void isTodoEqual_WithSecondTodoNameNull_ReturnFalse()
{
    todo second;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &second));
    free(second.name);
    second.name = NULL;
    TEST_ASSERT_FALSE(isTodoEqual(todoSample1, &second));
    freeTodoContent(&second);
}

void isTodoEqual_WithFirstAndSecondTodoNameNull_ReturnTrue()
{
    todo second;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &second));
    free(todoSample1->name);
    free(second.name);
    todoSample1->name = NULL;
    second.name = NULL;
    TEST_ASSERT_TRUE(isTodoEqual(todoSample1, &second));
    freeTodoContent(&second);
}

void isTodoEqual_WithSecondTodoRuntimeIdDiff_ReturnFalse()
{
    todo second;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &second));
    second.runtimeId = 99;
    TEST_ASSERT_FALSE(isTodoEqual(todoSample1, &second));
    freeTodoContent(&second);
}

void isTodoEqual_WithSecondTodoDescriptionDiff_ReturnFalse()
{
    todo second;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &second));
    second.description = malloc(sizeof(char) * 5);
    strcpy(second.description, "test");
    TEST_ASSERT_FALSE(isTodoEqual(todoSample1, &second));
    freeTodoContent(&second);
}

void isTodoEqual_WithFirstTodoDescriptionNull_ReturnFalse() 
{
    todo second;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &second));
    todoSample1->description = NULL;
    second.description = malloc(sizeof(char) * 5);
    strcpy(second.description, "test");
    TEST_ASSERT_FALSE(isTodoEqual(todoSample1, &second));
    freeTodoContent(&second);
}

void isTodoEqual_WithSecondTodoDescriptionNull_ReturnFalse() 
{
    todo second;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &second));
    second.description = NULL;
    todoSample1->description = malloc(sizeof(char) * 5);
    strcpy(todoSample1->description, "test");
    TEST_ASSERT_FALSE(isTodoEqual(todoSample1, &second));
    freeTodoContent(&second);
}

void isTodoEqual_WithFirstAndSecondTodoDescriptionNull_ReturnTrue() 
{
    todo second;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &second));
    todoSample1->description = NULL;
    second.description = NULL;
    TEST_ASSERT_TRUE(isTodoEqual(todoSample1, &second));
    freeTodoContent(&second);
}

void isTodoEqual_WithDateTimeDiff_ReturnFalse() 
{
    todo second;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &second));
    second.datetime = todoSample1->datetime + 5;
    TEST_ASSERT_FALSE(isTodoEqual(todoSample1, &second));
    freeTodoContent(&second);
}

void isTodoEqual_WithRuntimeIdDiff_ReturnFalse() 
{
    todo second;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &second));
    second.runtimeId = todoSample1->runtimeId + 5;
    TEST_ASSERT_FALSE(isTodoEqual(todoSample1, &second));
    freeTodoContent(&second);
}

void isTodoEqual_WithPriorityDiff_ReturnFalse() 
{
    todo second;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &second));
    second.priority = todoSample1->priority + 5;
    TEST_ASSERT_FALSE(isTodoEqual(todoSample1, &second));
    freeTodoContent(&second);
}

void isTodoEqual_WithAllFieldIdentical_ReturnTrue()
{
    todo second;
    TEST_ASSERT_EQUAL_INT(0, cloneTodo(todoSample1, &second));
    TEST_ASSERT_TRUE(isTodoEqual(todoSample1, &second));
    freeTodoContent(&second);
}