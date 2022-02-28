cmake_minimum_required(VERSION 3.10)

project(FileDuplicates VERSION 1.0.0 LANGUAGES CXX)

add_compile_options(-std=c++1z)

set(CLI_COMMAND_NAME fdups)
set(CLI_VERSION ${PROJECT_VERSION})
set(CLI_AUTHOR "Alex-53-8 <https://github.com/alex-53-8>")

add_subdirectory(libs)
add_subdirectory(app)
