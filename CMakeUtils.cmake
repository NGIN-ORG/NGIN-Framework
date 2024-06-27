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
        get_property(_SOURCE_DIR TARGET ${FETCHLIB_NAME} PROPERTY SOURCE_DIR)
        get_property(_BINARY_DIR TARGET ${FETCHLIB_NAME} PROPERTY BINARY_DIR)
        set(${FETCHLIB_NAME}_SOURCE_DIR ${_SOURCE_DIR} PARENT_SCOPE)
        set(${FETCHLIB_NAME}_BINARY_DIR ${_BINARY_DIR} PARENT_SCOPE)

        message(STATUS "Fetched ${FETCHLIB_NAME} at source directory: ${${FETCHLIB_NAME}_SOURCE_DIR}")
        message(STATUS "Fetched ${FETCHLIB_NAME} at binary directory: ${${FETCHLIB_NAME}_BINARY_DIR}")
    else ()
        message(STATUS "Found installed package ${FETCHLIB_NAME} at: ${${FETCHLIB_NAME}_DIR}")
    endif ()
endfunction()







# vulkan-hpp
#find_package(VulkanHeaders QUIET)
#if(UNIX)
#    set(VULKAN_HPP_NO_EXCEPTIONS ON CACHE BOOL "" FORCE)
#    fetch_dependency(vulkanHpp "https://github.com/KhronosGroup/Vulkan-Headers" "main")
#endif()