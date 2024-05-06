cmake_minimum_required(VERSION 3.27)
project(hesoyam)

set(CMAKE_CXX_STANDARD 20)

add_executable(cliong.exe university/2nd_sem/AlgoHomeWork/DCP/A.cpp)
set_target_properties(cliong.exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/university/2nd_sem/AlgoHomeWork/DCP/")