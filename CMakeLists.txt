cmake_minimum_required(VERSION 3.5)

project(dslither LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS system program_options thread fiber log REQUIRED)
find_package(Threads REQUIRED)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

#FetchContent_Populate(Catch2)

#include(${Catch2_SOURCE_DIR})
include(${Catch2_SOURCE_DIR}/contrib/Catch.cmake)
include(${Catch2_SOURCE_DIR}/contrib/ParseAndAddCatchTests.cmake)

#find_package(Catch2 REQUIRED)
#INCLUDE_DIRECTORIES (${Catch2_INCLUDE_DIRS})
set(dslither_SRC 
    src/slith.cpp 
    src/slith_node.cpp 
    src/point_indexer.cpp 
    src/powerup.cpp 
    src/powerup_manager.cpp
    src/gamestate.cpp 
    src/player.cpp 
    src/color.cpp)
set(dslither_HEADERS 
    src/slith.h 
    src/slith_node.h 
    src/point_indexer.h 
    src/powerup.h 
    src/powerup_manager.h
    src/gamestate.h 
    src/player.h 
    src/color.h)

add_library(dslith ${dslither_SRC} ${dslither_HEADERS} )
target_link_libraries(dslith Threads::Threads ${Boost_LIBRARIES})

add_executable(dslither src/main.cpp ${dslither_HEADERS})
target_link_libraries(dslither ${Boost_LIBRARIES} Threads::Threads dslith)

#add_subdirectory(tests) 

enable_testing()

INCLUDE_DIRECTORIES (${Catch2_INCLUDE_DIRS})
include_directories(..)
set(CMAKE_INCLUDE_CURRENT_DIR true)
set(dslither_test_SRC 
    tests/slith_tests.cpp
    tests/powerups_test.cpp
    tests/color_tests.cpp)

include_directories(src)
add_executable(dslither_tests tests/tests.cpp ${dslither_test_SRC} ${dslither_HEADERS})
target_link_libraries(dslither_tests Catch2::Catch2 ${Boost_LIBRARIES} dslith Threads::Threads)

include(CTest)
ParseAndAddCatchTests(dslither_tests) 