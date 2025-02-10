cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(renderers STATIC)

file(GLOB_RECURSE RENDERERS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(renderers PRIVATE ${RENDERERS_SOURCES})

target_include_directories(renderers PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/external
)

target_precompile_headers(renderers PRIVATE ${CMAKE_SOURCE_DIR}/src/pch.hpp)

target_link_libraries(renderers PUBLIC SFML::Graphics TGUI::TGUI)