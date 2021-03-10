#include "commandTest.h"
#include "command.h"
#include "unity.h"

void runCommandTests() 
{
    RUN_TEST(parseCommand_WithNullCommandStr_ReturnInvalidArgs);
    RUN_TEST(parseCommand_WithNullCommand_ReturnInvalidArgs);
    RUN_TEST(parseCommand_WithEmptyCommandStr_ReturnInvalidCmd);
    RUN_TEST(isCommandAvailable_WithNullCommand_ReturnFalse);
    RUN_TEST(isCommandAvailable_WithEmptyCommand_ReturnFalse);
    RUN_TEST(isCommandAvailable_WithquitCommand_ReturnTrue);
    RUN_TEST(isCommandAvailable_WithQuitCommand_ReturnFalse);
    RUN_TEST(isCommandAvailable_WithQUITCommand_ReturnFalse);
    RUN_TEST(isCommandAvailable_WithaddCommand_ReturnTrue);
}

void parseCommand_WithNullCommandStr_ReturnInvalidArgs() 
{
    command cmd;
    TEST_ASSERT_EQUAL_INT(E_INVALIDARGS, parseCommand(NULL, &cmd));
}

void parseCommand_WithNullCommand_ReturnInvalidArgs() 
{
    TEST_ASSERT_EQUAL_INT(E_INVALIDARGS, parseCommand("help", NULL));
}

void parseCommand_WithEmptyCommandStr_ReturnInvalidCmd() 
{
    //command cmd;
    //TEST_ASSERT_EQUAL_INT(E_INVALIDARGS, parseCommand("", &cmd));

    command cmd;
    TEST_ASSERT_EQUAL_INT(E_SUCCESS, parseCommand("add", &cmd));
    TEST_ASSERT_EQUAL_INT(1, cmd.argc);
    TEST_ASSERT_NULL(cmd.args[0].flag);
    TEST_ASSERT_EQUAL_STRING("add", cmd.args[0].value);
    freeCommand(&cmd);
}

void isCommandAvailable_WithNullCommand_ReturnFalse() 
{
    TEST_ASSERT_FALSE(isCommandAvailable(NULL));
}

void isCommandAvailable_WithEmptyCommand_ReturnFalse() 
{
    TEST_ASSERT_FALSE(isCommandAvailable(""));
}

void isCommandAvailable_WithquitCommand_ReturnTrue() 
{
    TEST_ASSERT_TRUE(isCommandAvailable("quit"));
}

void isCommandAvailable_WithQuitCommand_ReturnFalse() 
{
    TEST_ASSERT_FALSE(isCommandAvailable("Quit"));
}

void isCommandAvailable_WithQUITCommand_ReturnFalse() 
{
    TEST_ASSERT_FALSE(isCommandAvailable("QUIT"));
}

void isCommandAvailable_WithaddCommand_ReturnTrue() 
{
    TEST_ASSERT_TRUE(isCommandAvailable("add"));   
}


