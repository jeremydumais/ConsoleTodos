#ifndef TODOLISTTEST_H
#define TODOLISTTEST_H

void runTodoListTests();
void appendTodo_WithNullTodos_ReturnMinus1();
void appendTodo_WithEmptyTodos_Return0();
void appendTodo_WithNullItem_ReturnMinus1();
void appendTodo_ToAOneListItem_ReturnMinus0();

#endif