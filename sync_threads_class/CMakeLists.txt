cmake_minimum_required(VERSION 3.0.0)
project(sync VERSION 0.1.0)
find_package (Threads)

include(CTest)
enable_testing()

add_library(
	read
	read.cpp
	read.hpp
	)

add_library(
	write
	write.cpp
	write.hpp
	)

add_executable(sync main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D_LINUX -no-pie -lm")

include(CPack)
target_link_libraries(sync PRIVATE  read write  ${CMAKE_THREAD_LIBS_INIT} m)