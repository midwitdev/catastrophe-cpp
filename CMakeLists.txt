cmake_minimum_required(VERSION 3.0.0)
project(catastrophe VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(catastrophe src/catastrophe.cxx src/html.cxx)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
