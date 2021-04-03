#include "unity.h"
#include "todoStorageTest.h"

void setUp(void) {
}

void tearDown(void) {
}

int main(void) {
    UNITY_BEGIN();
    runTodoStorageTests();
    return UNITY_END();
}