cmake_minimum_required(VERSION 3.16)

project(ring_buffer_practice LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(ring_buffer ring_buffer.c)
target_include_directories(ring_buffer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_ring_buffer test_ring_buffer.c)
target_link_libraries(test_ring_buffer PRIVATE ring_buffer)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(ring_buffer PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(test_ring_buffer PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_test(NAME ring_buffer COMMAND test_ring_buffer)
