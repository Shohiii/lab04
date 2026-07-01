cmake_minimum_required(VERSION 3.10)
project(banking_project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0")

add_subdirectory(banking)

option(BUILD_TESTS "Build tests" ON)
if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  
  # Намертво отключаем превращение варнингов в ошибки внутри GTest
  target_compile_options(gtest PRIVATE -Wno-error)
  target_compile_options(gmock PRIVATE -Wno-error)
  
  file(GLOB TEST_SOURCES tests/*.cpp)
  add_executable(check ${TEST_SOURCES})
  target_link_libraries(check banking gtest_main gmock)
  add_test(NAME check COMMAND check)
endif()
