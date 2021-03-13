#include "commandTest.h"
#include "command.h"
#include "commandAdd.h"
#include "unity.h"

void runCommandTests() 
{
    RUN_TEST(parseCommand_WithNullCommandStr_ReturnInvalidArgs);
    RUN_TEST(parseCommand_WithNullCommand_ReturnInvalidArgs);
    RUN_TEST(parseCommand_WithEmptyCommandStr_ReturnInvalidCmd);
    RUN_TEST(parseCommand_WithZeroLengthCommand_ReturnInvalidArgs);
    RUN_TEST(parseCommand_WithhelpCommandStr_ReturnSuccess);
    RUN_TEST(parseCommand_WithaddWithoutArgsCommandStr_ReturnSuccess);
    RUN_TEST(parseCommand_WithaddAndTParamCommandStr_ReturnSuccess);
    RUN_TEST(parseCommand_WithaddAndTitleParamWithQuotedValue_ReturnSuccess);
    RUN_TEST(isCommandAvailable_WithNullCommand_ReturnFalse);
    RUN_TEST(isCommandAvailable_WithEmptyCommand_ReturnFalse);
    RUN_TEST(isCommandAvailable_WithquitCommand_ReturnTrue);
    RUN_TEST(isCommandAvailable_WithQuitCommand_ReturnFalse);
    RUN_TEST(isCommandAvailable_WithQUITCommand_ReturnFalse);
    RUN_TEST(isCommandAvailable_WithaddCommand_ReturnTrue);
    RUN_TEST(getArgumentsFromString_WithaddWithoutArgs_ReturnOneArg);
    RUN_TEST(getArgumentsFromString_WithaddWithTParamWithoutValue_ReturnTwoArg);
    RUN_TEST(getArgumentsFromString_WithaddWithTParamWithoutValueExtraSpaces_ReturnOneArg);
    RUN_TEST(getArgumentsFromString_WithaddWithTParamAndUnquotedValue_ReturnThreeArg);
    RUN_TEST(getArgumentsFromString_WithaddWithTParamAndQuotedValue_ReturnThreeArg);
    RUN_TEST(getArgumentsFromString_WithaddWithTitleParamAndQuotedValue_ReturnThreeArg);
    RUN_TEST(getArgumentsFromString_WithaddWithTAndPParam_ReturnFiveArg);
}

void parseCommand_WithNullCommandStr_ReturnInvalidArgs() 
{
    char cmd[20];
    void *cmdArgs;
    TEST_ASSERT_EQUAL_INT(E_INVALIDARGS, parseCommand(NULL, cmd, 20, cmdArgs));
}

void parseCommand_WithNullCommand_ReturnInvalidArgs() 
{
    void *cmdArgs;
    TEST_ASSERT_EQUAL_INT(E_INVALIDARGS, parseCommand("help", NULL, 20, cmdArgs));
}

void parseCommand_WithEmptyCommandStr_ReturnInvalidCmd() 
{
    char cmd[20];
    void *cmdArgs;
    TEST_ASSERT_EQUAL_INT(E_INVALIDCMD, parseCommand("", cmd, 20, cmdArgs));
}

void parseCommand_WithZeroLengthCommand_ReturnInvalidArgs() 
{
    char cmd[20];
    void *cmdArgs;
    TEST_ASSERT_EQUAL_INT(E_INVALIDARGS, parseCommand("help", cmd, 0, cmdArgs));
}

void parseCommand_WithhelpCommandStr_ReturnSuccess() 
{
    char cmd[20];
    void *cmdArgs;
    TEST_ASSERT_EQUAL_INT(E_SUCCESS, parseCommand("help", cmd, 20, &cmdArgs));
    TEST_ASSERT_EQUAL_STRING("help", cmd);
    TEST_ASSERT_NULL(cmdArgs);
    if (cmdArgs != NULL) {
        freeCommand(cmd, &cmdArgs);
    }
}

void parseCommand_WithaddWithoutArgsCommandStr_ReturnSuccess() 
{
    char cmd[20];
    void *cmdArgs;
    TEST_ASSERT_EQUAL_INT(E_REQUIREDARGSMISSING, parseCommand("add", cmd, 20, &cmdArgs));
}

void parseCommand_WithaddAndTParamCommandStr_ReturnSuccess() 
{
    char cmd[20];
    void *cmdArgs;
    TEST_ASSERT_EQUAL_INT(E_SUCCESS, parseCommand("add -t title", cmd, 20, &cmdArgs));
    commandAddArgs *addArg = (commandAddArgs *)cmdArgs;
    TEST_ASSERT_EQUAL_STRING("title", addArg->title);
    TEST_ASSERT_EQUAL_INT(3, addArg->priority);
    if (cmdArgs != NULL) {
        freeCommand(cmd, &cmdArgs);
    }
}

void parseCommand_WithaddAndTitleParamWithQuotedValue_ReturnSuccess() 
{
    char cmd[20];
    void *cmdArgs;
    TEST_ASSERT_EQUAL_INT(E_SUCCESS, parseCommand("add --title \"title test\"", cmd, 20, &cmdArgs));
    commandAddArgs *addArg = (commandAddArgs *)cmdArgs;
    TEST_ASSERT_EQUAL_STRING("title test", addArg->title);
    TEST_ASSERT_EQUAL_INT(3, addArg->priority);
    if (cmdArgs != NULL) {
        freeCommand(cmd, &cmdArgs);
    }
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

void getArgumentsFromString_WithaddWithoutArgs_ReturnOneArg() 
{
    char **argv;
    TEST_ASSERT_EQUAL_INT(1, _getArgumentsFromString("add", &argv));
    TEST_ASSERT_EQUAL_STRING("add", argv[0]);
}

void getArgumentsFromString_WithaddWithTParamWithoutValue_ReturnTwoArg() 
{
    char **argv;
    TEST_ASSERT_EQUAL_INT(2, _getArgumentsFromString("add -t", &argv));
    TEST_ASSERT_EQUAL_STRING("add", argv[0]);
    TEST_ASSERT_EQUAL_STRING("-t", argv[1]);
}

void getArgumentsFromString_WithaddWithTParamWithoutValueExtraSpaces_ReturnOneArg() 
{
    char **argv;
    TEST_ASSERT_EQUAL_INT(2, _getArgumentsFromString("   add      -t     ", &argv));
    TEST_ASSERT_EQUAL_STRING("add", argv[0]);
    TEST_ASSERT_EQUAL_STRING("-t", argv[1]);
}

void getArgumentsFromString_WithaddWithTParamAndUnquotedValue_ReturnThreeArg() 
{
    char **argv;
    TEST_ASSERT_EQUAL_INT(3, _getArgumentsFromString("add -t title", &argv));
    TEST_ASSERT_EQUAL_STRING("add", argv[0]);
    TEST_ASSERT_EQUAL_STRING("-t", argv[1]);
    TEST_ASSERT_EQUAL_STRING("title", argv[2]);
}

void getArgumentsFromString_WithaddWithTParamAndQuotedValue_ReturnThreeArg() 
{
    char **argv;
    TEST_ASSERT_EQUAL_INT(3, _getArgumentsFromString("add -t \"title test\"", &argv));
    TEST_ASSERT_EQUAL_STRING("add", argv[0]);
    TEST_ASSERT_EQUAL_STRING("-t", argv[1]);
    TEST_ASSERT_EQUAL_STRING("title test", argv[2]);
}

void getArgumentsFromString_WithaddWithTitleParamAndQuotedValue_ReturnThreeArg() 
{
    char **argv;
    TEST_ASSERT_EQUAL_INT(3, _getArgumentsFromString("add --title \"title test\"", &argv));
    TEST_ASSERT_EQUAL_STRING("add", argv[0]);
    TEST_ASSERT_EQUAL_STRING("--title", argv[1]);
    TEST_ASSERT_EQUAL_STRING("title test", argv[2]);
}

void getArgumentsFromString_WithaddWithTAndPParam_ReturnFiveArg() 
{
    char **argv;
    TEST_ASSERT_EQUAL_INT(5, _getArgumentsFromString("add -t test -p 3", &argv));
    TEST_ASSERT_EQUAL_STRING("add", argv[0]);
    TEST_ASSERT_EQUAL_STRING("-t", argv[1]);
    TEST_ASSERT_EQUAL_STRING("test", argv[2]);
    TEST_ASSERT_EQUAL_STRING("-p", argv[3]);
    TEST_ASSERT_EQUAL_STRING("3", argv[4]);
}
