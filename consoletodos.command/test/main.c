#include "unity.h"
#include "commandTest.h"

void setUp(void) {
}

void tearDown(void) {
}

int main(void) {
    UNITY_BEGIN();
    runCommandTests();
    return UNITY_END();
}