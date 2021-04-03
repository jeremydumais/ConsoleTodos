#include "typeUtilTest.h"
#include "typeUtil.h"
#include "unity.h"

void runTypeUtilTests() 
{
    RUN_TEST(isStringEmptyOrWhiteSpace_WithNullValue_ReturnTrue);
    RUN_TEST(isStringEmptyOrWhiteSpace_WithEmptyValue_ReturnTrue);
    RUN_TEST(isStringEmptyOrWhiteSpace_WithOneWSValue_ReturnTrue);
    RUN_TEST(isStringEmptyOrWhiteSpace_WithThreeWSValue_ReturnTrue);
    RUN_TEST(isStringEmptyOrWhiteSpace_WithTestSurroundedByWSValue_ReturnFalse);
    RUN_TEST(isStringEmptyOrWhiteSpace_WithTestAndWSValue_ReturnFalse);
    RUN_TEST(isStringEmptyOrWhiteSpace_WithWSAndTestValue_ReturnFalse);
}

void isStringEmptyOrWhiteSpace_WithNullValue_ReturnTrue() 
{
    TEST_ASSERT_TRUE(isStringEmptyOrWhiteSpace(NULL));
}

void isStringEmptyOrWhiteSpace_WithEmptyValue_ReturnTrue() 
{
    TEST_ASSERT_TRUE(isStringEmptyOrWhiteSpace(""));
}

void isStringEmptyOrWhiteSpace_WithOneWSValue_ReturnTrue() 
{
    TEST_ASSERT_TRUE(isStringEmptyOrWhiteSpace(" "));
}

void isStringEmptyOrWhiteSpace_WithThreeWSValue_ReturnTrue() 
{
    TEST_ASSERT_TRUE(isStringEmptyOrWhiteSpace("   "));
}

void isStringEmptyOrWhiteSpace_WithTestSurroundedByWSValue_ReturnFalse() 
{
    TEST_ASSERT_FALSE(isStringEmptyOrWhiteSpace("   test    "));
}

void isStringEmptyOrWhiteSpace_WithTestAndWSValue_ReturnFalse() 
{
    TEST_ASSERT_FALSE(isStringEmptyOrWhiteSpace("test    "));
}

void isStringEmptyOrWhiteSpace_WithWSAndTestValue_ReturnFalse() 
{
    TEST_ASSERT_FALSE(isStringEmptyOrWhiteSpace("    test"));
}
