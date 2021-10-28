cmake_minimum_required(VERSION 3.16)
project(hello)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_definitions("-Wall -Wextra -Werror")
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
add_executable(hello main.cpp)

execute_process( COMMAND ${CMAKE_COMMAND} -E copy
  ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
  ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
)

