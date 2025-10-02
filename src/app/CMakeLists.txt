set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(Calc main.cpp)
target_link_libraries(Calc PUBLIC CalcCore)
