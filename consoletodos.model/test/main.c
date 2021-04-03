#include "unity.h"
#include "todoTest.h"
#include "typeUtilTest.h"

void setUp(void) {
}

void tearDown(void) {
}

int main(void) {
    UNITY_BEGIN();
    runTodoTests();
    runTypeUtilTests();
    return UNITY_END();
}