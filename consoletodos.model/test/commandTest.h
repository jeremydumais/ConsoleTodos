#ifndef COMMAND_TEST_H
#define COMMAND_TEST_H

void runCommandTests();
void parseCommand_WithNullCommandStr_ReturnInvalidArgs();
void parseCommand_WithNullCommand_ReturnInvalidArgs();
void parseCommand_WithEmptyCommandStr_ReturnInvalidCmd();

void isCommandAvailable_WithNullCommand_ReturnFalse();
void isCommandAvailable_WithEmptyCommand_ReturnFalse();
void isCommandAvailable_WithquitCommand_ReturnTrue();
void isCommandAvailable_WithQuitCommand_ReturnFalse();
void isCommandAvailable_WithQUITCommand_ReturnFalse();
void isCommandAvailable_WithaddCommand_ReturnTrue();

#endif