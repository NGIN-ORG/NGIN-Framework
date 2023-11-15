# Dependencies Configuration
include(FetchContent)

# Function to handle dependency fetching
macro(fetch_dependency _name _repo _tag)
    # Try to find the package locally first
    find_package(${_name} QUIET)
    
    # If the package isn't found locally, use FetchContent to obtain it
    if(NOT ${_name}_FOUND)
        # Set the directory where the dependencies will be stored
        set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/dependencies/${_name}")

        FetchContent_Declare(${_name}
            GIT_REPOSITORY ${_repo}
            GIT_TAG ${_tag}
            GIT_SHALLOW TRUE
        )
        FetchContent_MakeAvailable(${_name})
    else()
        message(STATUS "Found ${_name} locally")
    endif()
endmacro()


# fmtlib

set(FMT_USE_NOEXCEPT ON CACHE BOOL "" FORCE)
fetch_dependency(fmt "https://github.com/fmtlib/fmt" "10.1.1")

# SDL2
set(SDL_TEST_ENABLED_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_VULKAN ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
fetch_dependency(SDL2 "https://github.com/libsdl-org/SDL" "release-2.28.5")

# GLM
fetch_dependency(glm "https://github.com/g-truc/glm" "0.9.9.8")

# JSON
set(JSON_BuildTests OFF CACHE INTERNAL "")
fetch_dependency(json "https://github.com/nlohmann/json" "v3.11.2")

set(RAPIDJSON_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(RAPIDJSON_BUILD_CXX17 ON CACHE BOOL "" FORCE)
set(RAPIDJSON_NOMEMBERITERATORCLASS ON CACHE BOOL "" FORCE)
fetch_dependency(rapidjson "https://github.com/Tencent/rapidjson" "v1.1.0")

# Google Test
set(BUILD_GTEST ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
fetch_dependency(googletest "https://github.com/google/googletest" "main")

# Vulkan
message(STATUS "Checking Vulkan path: $ENV{VULKAN_SDK}")

find_package(Vulkan REQUIRED)

# vulkan-hpp
#find_package(VulkanHeaders QUIET)
#if(UNIX)
#    set(VULKAN_HPP_NO_EXCEPTIONS ON CACHE BOOL "" FORCE)
#    fetch_dependency(vulkanHpp "https://github.com/KhronosGroup/Vulkan-Headers" "main")
#endif()