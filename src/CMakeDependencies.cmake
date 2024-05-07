include(FetchContent)

# Function to fetch a library and make it available along with its source and binary directories
function(FETCH_LIBRARY)
    # Parse arguments
    set(oneValueArgs NAME GIT_TAG GIT_REPOSITORY FORCE_FETCH)
    set(multiValueArgs OPTIONS)
    cmake_parse_arguments(FETCHLIB "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Validate required parameters
    if (NOT FETCHLIB_NAME OR NOT FETCHLIB_GIT_REPOSITORY OR NOT FETCHLIB_GIT_TAG)
        message(FATAL_ERROR "FETCH_LIBRARY called without specifying NAME, GIT_REPOSITORY, or GIT_TAG")
    endif ()

    # Try to find the package locally first
    if (NOT FORCE_FETCH)
        find_package(${FETCHLIB_NAME} QUIET)
    endif ()

    if (NOT ${FETCHLIB_NAME}_FOUND)
        # Use FetchContent to obtain the library
        FetchContent_Declare(${FETCHLIB_NAME}
                GIT_REPOSITORY ${FETCHLIB_GIT_REPOSITORY}
                GIT_TAG ${FETCHLIB_GIT_TAG}
        )

        # Apply user-specified options before making the library available
        foreach (OPTION IN LISTS FETCHLIB_OPTIONS)
            string(REPLACE " " ";" OPTION_PAIR ${OPTION})
            list(GET OPTION_PAIR 0 OPTION_NAME)
            list(GET OPTION_PAIR 1 OPTION_VALUE)
            set(${OPTION_NAME} ${OPTION_VALUE} CACHE INTERNAL "Set by FETCH_LIBRARY")
        endforeach ()

        # Make the library available
        FetchContent_MakeAvailable(${FETCHLIB_NAME})

        # Set global variables for source and binary directories
        set(${FETCHLIB_NAME}_SOURCE_DIR ${FETCHLIB_NAME}_SOURCE_DIR)
        set(${FETCHLIB_NAME}_BINARY_DIR ${FETCHLIB_NAME}_BINARY_DIR)

        message(STATUS "Fetched ${FETCHLIB_NAME} at: ${${FETCHLIB_NAME}_SOURCE_DIR} ")
    else ()
        message(STATUS "Found ${FETCHLIB_NAME} at: ${${FETCHLIB_NAME}_DIR} ")

    endif ()
endfunction()


# fmtlib

#set(FMT_USE_NOEXCEPT OFF CACHE BOOL "" FORCE)
#set(FMT_MODULE OFF CACHE BOOL "" FORCE)
#set(FMT_TEST OFF CACHE BOOL "" FORCE)
#set(FMT_ATTACH_TO_GLOBAL_MODULE OFF CACHE BOOL "" FORCE)
#set(FMT_INSTALL OFF CACHE BOOL "" FORCE)
#fetch_dependency(fmt "https://github.com/fmtlib/fmt" "10.2.1")

# SIMDString
FETCH_LIBRARY(
        NAME SIMDString
        GIT_REPOSITORY "https://github.com/NGIN-ORG/SIMDString"
        GIT_TAG "main"
)
# SDL2
#set(SDL_TEST_ENABLED_BY_DEFAULT OFF CACHE BOOL "" FORCE)
#set(SDL_TEST OFF CACHE BOOL "" FORCE)
#set(SDL_VULKAN ON CACHE BOOL "" FORCE)
#set(SDL_SHARED OFF CACHE BOOL "" FORCE)
#set(SDL_STATIC ON CACHE BOOL "" FORCE)
#fetch_dependency(SDL2 "https://github.com/libsdl-org/SDL" "release-2.28.5")

# GLM
FETCH_LIBRARY(
        NAME glm
        GIT_REPOSITORY "https://github.com/g-truc/glm"
        GIT_TAG "0.9.9.8"
        OPTIONS
        "GLM_BUILD_TESTS OFF"
        "GLM_BUILD_SHARED_LIBS OFF"
)

# JSON
FETCH_LIBRARY(
        NAME rapidjson
        GIT_REPOSITORY "https://github.com/Tencent/rapidjson"
        GIT_TAG "v1.1.0"
        FORCE_FETCH
        OPTIONS
        "RAPIDJSON_BUILD_DOC OFF"
        "RAPIDJSON_BUILD_EXAMPLES OFF"
        "RAPIDJSON_BUILD_TESTS OFF"
        "RAPIDJSON_BUILD_CXX17 ON"
        "RAPIDJSON_NOMEMBERITERATORCLASS ON"
)

FETCH_LIBRARY(
        NAME ut
        GIT_REPOSITORY "https://github.com/NGIN-ORG/ut"
        GIT_TAG "master"
        OPTIONS
        "BOOST_UT_DISABLE_MODULE ON"
        "BOOST_UT_BUILD_EXAMPLES OFF"
        "BOOST_UT_BUILD_TESTS OFF"
)

# Vulkan
message(STATUS "Checking Vulkan path: $ENV{VULKAN_SDK}")

find_package(Vulkan REQUIRED)

# vulkan-hpp
#find_package(VulkanHeaders QUIET)
#if(UNIX)
#    set(VULKAN_HPP_NO_EXCEPTIONS ON CACHE BOOL "" FORCE)
#    fetch_dependency(vulkanHpp "https://github.com/KhronosGroup/Vulkan-Headers" "main")
#endif()