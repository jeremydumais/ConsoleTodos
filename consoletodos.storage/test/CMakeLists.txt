set(PROJECT_NAME   "consoletodos.storage.test")

add_executable(${PROJECT_NAME} main.c todoStorageTest.c)

target_link_libraries(${PROJECT_NAME} consoletodos.storage unity)

add_test(AllTestsInConsoleStorageTest ${PROJECT_NAME})