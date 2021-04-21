#include "main.h"
#include "unity.h"
#include "todoTest.h"
#include "typeUtilTest.h"

todoList emptyTodoList;
todo *todoSample1;

void setUp(void) {
    emptyTodoList.list = NULL;
    emptyTodoList.length = 0;
    emptyTodoList.lastRuntimeId = 0;

    todoSample1 = createTodo("Sample1");
}

void tearDown(void) {
    freeTodoList(&emptyTodoList);
    freeTodo(todoSample1);
}

int main(void) {
    UNITY_BEGIN();
    runTodoTests();
    runTypeUtilTests();
    runTodoListTests();
    return UNITY_END();
}