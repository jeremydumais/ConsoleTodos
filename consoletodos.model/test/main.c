#include "unity.h"
#include "todoTest.h"

void setUp(void) {
}

void tearDown(void) {
}

int main(void) {
    UNITY_BEGIN();
    runTodoTests();
    return UNITY_END();
}