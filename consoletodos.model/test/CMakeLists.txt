set(PROJECT_NAME   "consoletodos.model.test")

add_executable(${PROJECT_NAME} main.c commandTest.c)

target_link_libraries(${PROJECT_NAME} consoletodos.model unity)

add_test(AllTestsInMain ${PROJECT_NAME})