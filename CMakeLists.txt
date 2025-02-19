cmake_minimum_required(VERSION 3.28.3)

# create compile_commands.json for lsp
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# prevent in-source builds
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "Please make a build directory.")
endif()

project(cpp-http-webserver
        DESCRIPTION "A simple HTTP1.1 webserver written in c++."
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_subdirectory(src)

# # enable for future tests
# enable_testing()
# add_subdirectory(test)

