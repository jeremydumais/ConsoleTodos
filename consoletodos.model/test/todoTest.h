#ifndef TODOTEST_H
#define TODOTEST_H

void runTodoTests();
void createTodo_WithNullName_ReturnMinus1();
void createTodo_WithEmptyName_ReturnMinus1();
void createTodo_WithWhiteSpaceName_ReturnMinus1();
void createTodo_WithOneCharName_Return0();

#endif