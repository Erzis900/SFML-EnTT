cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

# Add include directories
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/external)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/components)
include_directories(${CMAKE_SOURCE_DIR}/src/entities)
include_directories(${CMAKE_SOURCE_DIR}/src/systems)
include_directories(${CMAKE_SOURCE_DIR}/src/renderers)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Fetch and configure SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Fetch and configure TGUI
set(TGUI_BACKEND SFML_GRAPHICS)
FetchContent_Declare(
  TGUI
  GIT_REPOSITORY https://github.com/texus/TGUI
  GIT_TAG v1.7.0
)
FetchContent_MakeAvailable(TGUI)

# Add the features directory (this will build the features library)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/features)

# Collect source files for the main executable
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

# Create the main executable
add_executable(main ${SOURCES})

# Enable precompiled headers for the main executable
target_precompile_headers(main PRIVATE ${CMAKE_SOURCE_DIR}/src/pch.hpp)

# Link dependencies for the main executable
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE features SFML::Graphics TGUI::TGUI)