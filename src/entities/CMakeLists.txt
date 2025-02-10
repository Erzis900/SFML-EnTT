cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(entities STATIC)

file(GLOB_RECURSE ENTITIES_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(entities PRIVATE ${ENTITIES_SOURCES})

target_include_directories(entities PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/external
)

target_precompile_headers(entities PRIVATE ${CMAKE_SOURCE_DIR}/src/pch.hpp)

target_link_libraries(entities PUBLIC SFML::Graphics TGUI::TGUI)