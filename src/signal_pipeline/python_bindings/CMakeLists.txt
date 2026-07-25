cmake_minimum_required(VERSION 3.16)

project(signal_pipeline_python_bindings)

# ------------------------------------------------------------------
# C++ Standard
# ------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ------------------------------------------------------------------
# Find pybind11
# ------------------------------------------------------------------
find_package(pybind11 REQUIRED)

# ------------------------------------------------------------------
# Include standalone library headers
# ------------------------------------------------------------------
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../standalone_library/include
)

# ------------------------------------------------------------------
# Build Python module
# ------------------------------------------------------------------
pybind11_add_module(signal_pipeline
    bindings.cpp
)

# ------------------------------------------------------------------
# Include directories
# ------------------------------------------------------------------
target_include_directories(signal_pipeline PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../standalone_library/include
)

# ------------------------------------------------------------------
# Compiler warnings
# ------------------------------------------------------------------
if(MSVC)
    target_compile_options(signal_pipeline PRIVATE /W4)
else()
    target_compile_options(signal_pipeline PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endif()

# ------------------------------------------------------------------
# Install Python module into the ROS workspace
# ------------------------------------------------------------------
install(
    TARGETS signal_pipeline
    LIBRARY DESTINATION lib/python3.12/site-packages
)
