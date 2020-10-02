project(testingtarget)


enable_testing()

INCLUDE_DIRECTORIES (${Catch2_INCLUDE_DIRS})
include_directories(..)
set(CMAKE_INCLUDE_CURRENT_DIR true)
set(dslither_test_SRC 
    slith_tests.cpp)
add_executable(dslither_tests tests.cpp ${dslither_test_SRC} )
target_link_libraries(dslither_tests Catch2::Catch2 ${Boost_LIBRARIES} dslith Threads::Threads)

include(CTest)
include(ParseAndAddCatchTests)
ParseAndAddCatchTests(dslither) 