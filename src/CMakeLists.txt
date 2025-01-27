cmake_minimum_required(VERSION 3.10)

# Project Name
project(LexerProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCE_FILES
    main.cpp
    Lexer.cpp
    Token.cpp
)

# Add the executable
add_executable(LexerDriver ${SOURCE_FILES})

# Include directories
target_include_directories(LexerDriver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set output directories for compiled files
set_target_properties(LexerDriver PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    OUTPUT_NAME lexer
)

# Enable warnings (optional, but recommended)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(LexerDriver PRIVATE -Wall -Wextra -Wpedantic)
elseif (MSVC)
    target_compile_options(LexerDriver PRIVATE /W4 /permissive-)
endif()
