set(PROJECT_NAME   "consoletodos")

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c 
                               ${CMAKE_CURRENT_SOURCE_DIR}/src/shellUtil.c)
                               if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU") #gcc
target_link_libraries(${PROJECT_NAME} consoletodos.command readline)
# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
target_compile_options(${PROJECT_NAME}
    PRIVATE "-Wfatal-errors" # stops on first error
    "-Wall" # enables all the warnings about constructions
    "-Wextra" # Print extra warning messages"
    "-Werror=misleading-indentation" # Make all warnings into errors.
    "-pedantic" # Issue all the warnings demanded by strict ISO C and ISO C++
    "-pedantic-errors" # Like -pedantic, except that errors are produced rather than warnings http://stackoverflow.com/questions/30255294/how-to-hide-extra-output-from-pragma-message
    "-ftrack-macro-expansion=0"
    "-fno-diagnostics-show-caret"
    "-Wno-misleading-indentation"
    )
endif()