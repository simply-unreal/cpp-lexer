cmake_minimum_required(VERSION 3.20)

project(Cpp-Lexer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(Cpp-Lexer
    src/main.cpp
    src/lexer.cpp
)

set_target_properties(Cpp-Lexer PROPERTIES
    COMPILE_WARNING_AS_ERROR ON
)

target_include_directories(Cpp-Lexer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)