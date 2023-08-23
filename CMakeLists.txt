# create project
cmake_minimum_required(VERSION 3.23.0)
project(MasterMind VERSION 0.1.0 LANGUAGES CXX)

include(conan.cmake)

conan_cmake_configure(REQUIRES gtest/cci.20210126 GENERATORS CMakeToolchain)
conan_cmake_install(PATH_OR_REFERENCE . BUILD missing SETTING ${settings})
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

add_library(MasterMind src/game.cpp)
target_include_directories(MasterMind PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_features(MasterMind PUBLIC cxx_std_23)
add_executable(Game src/main.cpp)
target_link_libraries(Game PRIVATE MasterMind)


add_executable(tests test/test.cpp)
target_link_directories(tests PRIVATE ${CMAKE_LIBRARY_PATH})
target_link_libraries(tests gtest_main gtest gmock gmock_main MasterMind)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_INCLUDE_PATH})