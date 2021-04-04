#ifndef TODOTEST_H
#define TODOTEST_H

void runTodoTests();
void createTodo_WithNullTodo_ReturnMinus1();
void createTodo_WithNullName_ReturnMinus1();
void createTodo_WithEmptyName_ReturnMinus1();
void createTodo_WithWhiteSpaceName_ReturnMinus1();
void createTodo_WithOneCharName_Return0();

void updateTodo_WithNullTodo_ReturnMinus1();
void updateTodo_WithNullName_ReturnMinus1();
void updateTodo_WithEmptyName_ReturnMinus1();
void updateTodo_WithWhiteSpaceName_ReturnMinus1();
void updateTodo_WithValidDifferentName_Return0();
void updateTodo_WithValidSameName_Return0();
#endif