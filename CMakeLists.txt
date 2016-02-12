cmake_minimum_required(VERSION 2.6)
project(toylang)

include_directories(src/inc)

file(GLOB SOURCES "src/cpp/*.cpp")

add_executable(toylang ${SOURCES})
target_compile_features(toylang PRIVATE cxx_generalized_initializers)
