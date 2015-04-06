SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=gnu++11 -Wall -Wextra -pedantic ")

cmake_minimum_required (VERSION 2.8.11)
project (parallel_lcm)

find_package (Threads REQUIRED)

add_executable (parallel_lcm worker.cpp queue.cpp parallel_lcm.cpp math.cpp)
target_link_libraries (parallel_lcm ${CMAKE_THREAD_LIBS_INIT} gmp gmpxx)
