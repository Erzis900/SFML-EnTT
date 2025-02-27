cmake_minimum_required(VERSION 3.28)
project(SFML_RPG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set(CMAKE_CXX_COMPILER_LAUNCHER ccache)
endif()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/external)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/components)
include_directories(${CMAKE_SOURCE_DIR}/src/entities)
include_directories(${CMAKE_SOURCE_DIR}/src/systems)
include_directories(${CMAKE_SOURCE_DIR}/src/renderers)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)

FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

set(TGUI_BACKEND SFML_GRAPHICS)
FetchContent_Declare(
  TGUI
  GIT_REPOSITORY https://github.com/texus/TGUI
  GIT_TAG v1.7.0
)
FetchContent_MakeAvailable(TGUI)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/features)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/entities)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/renderers)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/systems)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

add_executable(main ${SOURCES})

target_precompile_headers(main PRIVATE ${CMAKE_SOURCE_DIR}/src/pch.hpp)
target_link_libraries(main PRIVATE features entities renderers systems SFML::Graphics SFML::Audio TGUI::TGUI)