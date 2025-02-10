cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(features STATIC)

file(GLOB_RECURSE FEATURES_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(features PRIVATE ${FEATURES_SOURCES})

target_include_directories(features PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/external
)

target_precompile_headers(features PRIVATE ${CMAKE_SOURCE_DIR}/src/pch.hpp)

target_link_libraries(features PUBLIC SFML::Graphics TGUI::TGUI)