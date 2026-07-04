cmake_minimum_required(VERSION 3.16)

project(packet_queue_practice LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_library(packet_queue packet_queue.c)
target_include_directories(packet_queue PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_packet_queue test_packet_queue.c)
target_link_libraries(test_packet_queue PRIVATE packet_queue)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(packet_queue PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(test_packet_queue PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
add_test(NAME packet_queue COMMAND test_packet_queue)
