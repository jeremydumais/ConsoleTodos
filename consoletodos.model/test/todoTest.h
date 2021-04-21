#ifndef TODOTEST_H
#define TODOTEST_H

void runTodoTests();
void createTodo_WithNullName_ReturnNULL();
void createTodo_WithEmptyName_ReturnNULL();
void createTodo_WithWhiteSpaceName_ReturnNULL();
void createTodo_WithOneCharName_ReturnSuccess();

void updateTodo_WithNullTodo_ReturnMinus1();
void updateTodo_WithNullName_ReturnMinus1();
void updateTodo_WithEmptyName_ReturnMinus1();
void updateTodo_WithWhiteSpaceName_ReturnMinus1();
void updateTodo_WithValidDifferentName_Return0();
void updateTodo_WithValidSameName_Return0();

void freeTodo_WithNullTodo_ReturnSuccess();
void freeTodo_WithNonNullTodo_ReturnSuccess();

void freeTodoContent_WithNullTodo_ReturnSuccess();

void cloneTodo_WithValidSrcAndOnlyName_DoNothing();

#endif