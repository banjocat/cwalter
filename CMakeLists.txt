cmake_minimum_required (VERSION 3.0)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-g")

include_directories(src tests)
project (cwalter VERSION 0.1)
add_library(cwalter SHARED ./src/cwalter.c)
target_link_libraries(cwalter ssh)
project (run_tests)
add_executable(run_tests ./tests/test.c)
target_link_libraries(run_tests cwalter)

install (TARGETS cwalter DESTINATION include)
