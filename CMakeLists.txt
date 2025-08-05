cmake_minimum_required(VERSION 3.30)
set(CURRENT_PROJECT "bank")

project(${CURRENT_PROJECT} C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Threads REQUIRED)

add_executable(${CURRENT_PROJECT}
    ${PROJECT_SOURCE_DIR}/src/main.c
    ${PROJECT_SOURCE_DIR}/src/bank.c
    ${PROJECT_SOURCE_DIR}/src/utils.c
)

target_include_directories(${CURRENT_PROJECT} PRIVATE
    include
    ${PROJECT_SOURCE_DIR}/lib/uthash-2.3.0/src
)

target_compile_options(${CURRENT_PROJECT} PRIVATE /W4 /WX)

target_link_libraries(${CURRENT_PROJECT} PRIVATE
    Threads::Threads
)

