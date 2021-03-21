cmake_minimum_required(VERSION 3.16)
project("consoletodos" LANGUAGES C)

enable_testing()

# Download and unpack unity at configure time
configure_file(CMakeLists.txt.in unity-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/unity-download )
if(result)
  message(FATAL_ERROR "CMake step for unity-download failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/unity-download )
if(result)
  message(FATAL_ERROR "Build step for unity-download failed: ${result}")
endif() 
# Configure and build unity at configure time
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/unity-src )
if(result)
  message(FATAL_ERROR "CMake step for unity-src failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/unity-src )
if(result)
  message(FATAL_ERROR "Build step for unity-src failed: ${result}")
endif() 
include_directories(${CMAKE_CURRENT_BINARY_DIR}/unity-src/src)
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/unity-src EXCLUDE_FROM_ALL)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/consoletodos.model/src
                    ${CMAKE_CURRENT_SOURCE_DIR}/consoletodos.command/src
                    ${CMAKE_CURRENT_SOURCE_DIR}/consoletodos.storage/src)

add_subdirectory(consoletodos.model)
add_subdirectory(consoletodos.command)
add_subdirectory(consoletodos.storage)
add_subdirectory(consoletodos)
