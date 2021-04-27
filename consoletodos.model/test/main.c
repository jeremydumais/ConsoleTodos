#include "main.h"
#include "unity.h"
#include "todoTest.h"
#include "typeUtilTest.h"

todoList emptyTodoList;
todoList oneItemTodoList;
todo *todoSample1;
todo *todoSample2;

void setUp(void) {
    emptyTodoList.list = NULL;
    emptyTodoList.length = 0;
    emptyTodoList.lastRuntimeId = 0;

    todoSample1 = createTodo("Sample1");

    todoSample2 = createTodo("Sample2");
    appendTodo(&oneItemTodoList, todoSample2);
}

void tearDown(void) {
    freeTodo(&todoSample2);
    freeTodoList(&oneItemTodoList);

    freeTodo(&todoSample1);
    freeTodoList(&emptyTodoList);
}

int main(void) {
    UNITY_BEGIN();
    runTodoTests();
    runTypeUtilTests();
    runTodoListTests();
    return UNITY_END();
}