cmake_minimum_required(VERSION 3.10)
project(CalcCore)

# compile settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


set(sources 
    src/ast/ast.cpp
    src/ast/typetable.cpp
    src/compile/lexer.cpp
    src/compile/parser.cpp
    src/compile/compiler.cpp
    src/runtime/vm.cpp
    src/utils/utils.cpp
    src/utils/printast.cpp
)

add_library(${PROJECT_NAME} STATIC ${sources})

target_include_directories(${PROJECT_NAME} PUBLIC include)
