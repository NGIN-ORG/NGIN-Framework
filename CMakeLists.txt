set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)
cmake_minimum_required(VERSION 3.28)

project("NGIN" VERSION 0.1)

# enable c and c++
enable_language(C CXX)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


option(NGIN_BUILD_TESTS "Build NGIN tests" OFF)
message(STATUS "Build NGIN tests: ${NGIN_BUILD_TESTS}")

option(NGIN_BUILD_EXAMPLES "Build NGIN examples" ON)
message(STATUS "Build NGIN examples: ${NGIN_BUILD_EXAMPLES}")

option(NGIN_SHARED "Link NGIN as a shared library" OFF)
message(STATUS "Build NGIN as a shared library: ${NGIN_SHARED}")

option(NGIN_BUILD_DOCUMENTATION "Build NGIN documentation" OFF)
message(STATUS "Build documentation: ${NGIN_BUILD_DOCUMENTATION}")

option(NGIN_BUILD_ONLY_DOCUMENTATION "Build only documentation" OFF)
message(STATUS "Build only documentation: ${NGIN_BUILD_ONLY_DOCUMENTATION}")

option(NGIN_STRICT_WARNINGS "Enable strict warnings" OFF)
message(STATUS "Strict warnings: ${NGIN_STRICT_WARNINGS}")


option(NIGN_TEST_ON_BUILD "Run tests on build" OFF)
message(STATUS "Run tests on build: ${NIGN_TEST_ON_BUILD}")

option(NGIN_ENABLE_RTTI "Enable RTTI" ON)
message(STATUS "Enable RTTI: ${NGIN_ENABLE_RTTI}")

option(NGIN_DEFINE_MAIN "Define main function" ON)
message(STATUS "Define main function: ${NGIN_DEFINE_MAIN}")

#Check what platform we are building on
if (WIN32)
    add_compile_definitions(NGIN_PLATFORM_WINDOWS)
elseif (APPLE)
    add_compile_definitions(NGIN_PLATFORM_MACOS)
elseif (UNIX)
    add_compile_definitions(NGIN_PLATFORM_LINUX)
endif ()

# Check the build type and add respective compile options
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(NGIN_DEBUG)
    if (MSVC)
        add_compile_options(/Zi /Ob0 /Od)   # Debugging info, no inline expansion, no optimization
    else ()
        add_compile_options(-g)             # Debugging info for GCC/Clang
    endif ()
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(NGIN_RELEASE)
    if (MSVC)
        add_compile_options(/O2)
    else ()
        add_compile_options(-O3)
    endif ()

elseif (CMAKE_BUILD_TYPE STREQUAL "Dist")
    add_compile_definitions(NGIN_DIST)
    if (MSVC)
        add_compile_options(/O2)
    else ()
        add_compile_options(-O3)
    endif ()
else ()
    message(WARNING "Unknown build type: ${CMAKE_BUILD_TYPE}")
endif ()

if (NGIN_STRICT_WARNINGS)
    if (MSVC)
        add_compile_options(/W4)
    else ()
        add_compile_options(-Wall -Wextra -pedantic)
    endif ()
endif ()

if (NOT NGIN_BUILD_SHARED)
    add_compile_definitions(NGIN_BUILD_STATIC)
endif ()

if (NGIN_ENABLE_RTTI)
    add_compile_definitions(NGIN_ENABLE_RTTI)
endif ()

if (NGIN_DEFINE_MAIN)
    add_compile_definitions(NGIN_DEFINE_MAIN)
endif ()

#Add NGIN::Framework target
add_subdirectory(src)

if (NGIN_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

enable_testing()
include(CTest)
add_subdirectory(tests)