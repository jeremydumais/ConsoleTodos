#include "unity.h"
#include "todo.h"

void setUp(void) {
}

void tearDown(void) {
}

/*void addressGetFullName_WithNULLAddress_ReturnMinus1(void) {
    char fullname[FULLNAMESIZE];
    TEST_ASSERT_EQUAL_INT(-1, addressGetFullName(NULL, fullname));
}

void addressGetFullName_WithNULLFullname_ReturnMinus1() {
    address addr1;
    TEST_ASSERT_EQUAL_INT(-1, addressGetFullName(&addr1, NULL));
}*/

int main(void) {
    UNITY_BEGIN();
    //RUN_TEST(addressGetFullName_WithNULLAddress_ReturnMinus1);
    //RUN_TEST(addressGetFullName_WithNULLFullname_ReturnMinus1);
    return UNITY_END();
}