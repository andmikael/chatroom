cmake_minimum_required(VERSION 3.26)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")

project (server VERSION "0.1.1" LANGUAGES C)
add_executable(${PROJECT_NAME} server.c socketutil.c helper.c)

target_compile_options(${PROJECT_NAME} PRIVATE -w)