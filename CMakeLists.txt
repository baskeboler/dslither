cmake_minimum_required(VERSION 3.5)

project(dslither LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS system program_options thread fiber log REQUIRED)
find_package(Threads REQUIRED)

find_package(Catch2 REQUIRED)
INCLUDE_DIRECTORIES (${Catch2_INCLUDE_DIRS})
set(dslither_SRC slith.cpp slith_node.cpp point_indexer.cpp powerup.cpp powerup_manager.cpp
    )
set(dslither_HEADERS slith.h slith_node.h point_indexer.h powerup.h powerup_manager.h
    )
add_library(dslith ${dslither_SRC} ${dslither_HEADERS} )
target_link_libraries(dslith Threads::Threads ${Boost_LIBRARIES})

add_executable(dslither main.cpp ${dslither_HEADERS})
target_link_libraries(dslither ${Boost_LIBRARIES} Threads::Threads dslith)

#add_subdirectory(tests) 

enable_testing()

INCLUDE_DIRECTORIES (${Catch2_INCLUDE_DIRS})
include_directories(..)
set(CMAKE_INCLUDE_CURRENT_DIR true)
set(dslither_test_SRC 
    tests/slith_tests.cpp
    tests/powerups_test.cpp)
add_executable(dslither_tests tests/tests.cpp ${dslither_test_SRC})
target_link_libraries(dslither_tests Catch2::Catch2 ${Boost_LIBRARIES} dslith Threads::Threads)

include(CTest)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(dslither_tests) 