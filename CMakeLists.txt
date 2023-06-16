cmake_minimum_required(VERSION 3.0.0)
project(jesse-wasm-jit VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
include(CTest)
enable_testing()
add_subdirectory(test)
aux_source_directory(${CMAKE_CURRENT_LIST_DIR}/src sources)

add_executable(jesse-wasm-jit ${sources} main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
