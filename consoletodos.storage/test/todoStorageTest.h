#ifndef TODOSTORAGE_TEST_H
#define TODOSTORAGE_TEST_H

void runTodoStorageTests();
void createTodosFromJSONString_WithNullStr_ReturnZeroTodo();
void createTodosFromJSONString_WithEmptyStr_ReturnZeroTodo();
void createTodosFromJSONString_WithWhiteSpacesStr_ReturnZeroTodo();
void createTodosFromJSONString_WithNotArrayStr_ReturnZeroTodo();
void createTodosFromJSONString_WithEmptyArrayStr_ReturnZeroTodo();
void createTodosFromJSONString_WithOneTodoOnlyNameStr_ReturnOneTodo();

#endif