cmake_minimum_required(VERSION 3.14...3.31)

project(
    PostHogC
    VERSION 0.1.0
    DESCRIPTION "PostHogC"
    LANGUAGES C
)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Compiler flags
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic -Wno-unused-parameter")

# Debug flags
set(CMAKE_C_FLAGS_DEBUG "-g -O0")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(CMAKE_C_FLAGS_TEST "-g -O0 -DPHC_TEST")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Test" CACHE STRING "Configurations" FORCE)

# Find curl
find_package(CURL REQUIRED)

# PostHogC library
add_subdirectory(src)

# Tests
add_subdirectory(tests)
