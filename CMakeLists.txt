cmake_minimum_required(VERSION 3.16)

project(packet_shortener
    VERSION 2.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(packet_shortener
    src/main.cpp
    src/packet_shortener.cpp
)

target_include_directories(packet_shortener PRIVATE include)

if (MSVC)
    target_compile_options(packet_shortener PRIVATE /W4 /permissive-)
else()
    target_compile_options(packet_shortener PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()

add_executable(packet_shortener_tests
    tests/test_packet_shortener.cpp
    src/packet_shortener.cpp
)

target_include_directories(packet_shortener_tests PRIVATE include)

add_test(NAME packet_shortener_tests COMMAND packet_shortener_tests)
