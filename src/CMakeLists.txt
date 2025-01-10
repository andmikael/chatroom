cmake_minimum_required(VERSION 3.26)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")

project (chatroom VERSION "0.1.1" LANGUAGES C)
add_executable(${PROJECT_NAME} main.c)

# message(STATUS  ${CMAKE_SOURCE_DIR}) 

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.40.5/CPM.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=c46b876ae3b9f994b4f05a4c15553e0485636862064f1fcc9d8b4f832086bc5d
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

CPMAddPackage(
    NAME raylib
    GITHUB_REPOSITORY raysan5/raylib
    GIT_TAG 5.0
    VERSION 5.0
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE raylib)

target_compile_options(${PROJECT_NAME} PRIVATE -w)
