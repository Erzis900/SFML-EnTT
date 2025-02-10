cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(systems STATIC)

file(GLOB_RECURSE SYSTEMS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(systems PRIVATE ${SYSTEMS_SOURCES})

target_include_directories(systems PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/external
)

target_precompile_headers(systems PRIVATE ${CMAKE_SOURCE_DIR}/src/pch.hpp)

target_link_libraries(systems PUBLIC SFML::Graphics TGUI::TGUI)