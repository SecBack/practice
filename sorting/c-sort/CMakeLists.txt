cmake_minimum_required(VERSION 4.0)

project(MyProject)

include_directories(../../threadpool)
add_executable(main sort.c tests.c ../../threadpool/threadpool.c main.c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")