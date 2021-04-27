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

void cloneTodo_WithValidNullSrc_ReturnMinus1();
void cloneTodo_WithValidNullDst_ReturnMinus1();
void cloneTodo_WithValidSrcAndOnlyName_ReturnZero();

void isTodoEqual_WithNullFirstAndNotNullSecond_ReturnFalse();
void isTodoEqual_WithNullNotNullAndSecondNull_ReturnFalse();
void isTodoEqual_WithFirstAndSecondNull_ReturnTrue();
void isTodoEqual_WithSecondTodoNameDiff_ReturnFalse();
void isTodoEqual_WithFirstTodoNameNull_ReturnFalse();
void isTodoEqual_WithSecondTodoNameNull_ReturnFalse();
void isTodoEqual_WithFirstAndSecondTodoNameNull_ReturnTrue();
void isTodoEqual_WithSecondTodoRuntimeIdDiff_ReturnFalse();
void isTodoEqual_WithSecondTodoDescriptionDiff_ReturnFalse();
void isTodoEqual_WithFirstTodoDescriptionNull_ReturnFalse();
void isTodoEqual_WithSecondTodoDescriptionNull_ReturnFalse();
void isTodoEqual_WithFirstAndSecondTodoDescriptionNull_ReturnTrue();
void isTodoEqual_WithDateTimeDiff_ReturnFalse();
void isTodoEqual_WithRuntimeIdDiff_ReturnFalse();
void isTodoEqual_WithPriorityDiff_ReturnFalse();
void isTodoEqual_WithAllFieldIdentical_ReturnTrue();
#endif