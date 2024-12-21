cmake_minimum_required(VERSION 3.14)

# Create a library target for the features directory
add_library(features STATIC)

# Add source files for the features library
file(GLOB_RECURSE FEATURES_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/player/components/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/player/systems/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/player/entities/*.cpp"
)

target_sources(features PRIVATE ${FEATURES_SOURCES})

# Include directories for the features library
target_include_directories(features PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/entt)

# Link dependencies for the features library
target_link_libraries(features PUBLIC sfml-graphics)

# Set the C++ standard to C++17
target_compile_features(features PUBLIC cxx_std_17)