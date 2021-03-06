set(PROJECT_NAME   "consoletodos.command")

add_library(${PROJECT_NAME} SHARED ${CMAKE_CURRENT_SOURCE_DIR}/src/command.c
                                   ${CMAKE_CURRENT_SOURCE_DIR}/src/commandHelp.c
                                   ${CMAKE_CURRENT_SOURCE_DIR}/src/commandAdd.c
                                   ${CMAKE_CURRENT_SOURCE_DIR}/src/commandShow.c
                                   ${CMAKE_CURRENT_SOURCE_DIR}/src/commandLoad.c                 
                                   ${CMAKE_CURRENT_SOURCE_DIR}/src/commandUtil.c               
                                   ${CMAKE_CURRENT_SOURCE_DIR}/src/commandUpdate.c              
                                   ${CMAKE_CURRENT_SOURCE_DIR}/src/commandRemove.c                 
                                   ${CMAKE_CURRENT_SOURCE_DIR}/src/commandSave.c)                 

target_link_libraries(${PROJECT_NAME} consoletodos.model consoletodos.storage)
if ("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU") #gcc
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

add_subdirectory(test)