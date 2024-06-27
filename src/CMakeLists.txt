

include(${CMAKE_SOURCE_DIR}/include/CMakeHeaders.cmake)
include(${CMAKE_SOURCE_DIR}/src/CMakeSources.cmake)
include(${CMAKE_SOURCE_DIR}/CMakeUtils.cmake)


# Determine library type
if (NGIN_SHARED)
    set(NGIN_BUILD_TYPE SHARED)
else ()
    set(NGIN_BUILD_TYPE STATIC)
endif ()

add_library(NGIN ${NGIN_BUILD_TYPE})

if (NGIN_SHARED)
    target_compile_definitions(NGIN PRIVATE NGIN_BUILD_SHARED)
endif ()

target_sources(NGIN PRIVATE
        NGIN.cpp
        ${NGIN_ALL_SRC_FILES}
)
target_include_directories(NGIN PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        ${CMAKE_BINARY_DIR}/include
)


FETCH_LIBRARY(
        NAME fmt
        GIT_REPOSITORY "https://github.com/fmtlib/fmt"
        GIT_TAG "10.2.1"
        OPTIONS
        "FMT_TEST OFF"
        "FMT_INSTALL OFF"
)

# SIMDString
FETCH_LIBRARY(
        NAME SIMDString
        GIT_REPOSITORY "https://github.com/NGIN-ORG/SIMDString"
        GIT_TAG "main"
)

FETCH_LIBRARY(
        NAME glm
        GIT_REPOSITORY "https://github.com/g-truc/glm"
        GIT_TAG "0.9.9.8"
        OPTIONS
        "GLM_BUILD_TESTS OFF"
        "GLM_BUILD_SHARED_LIBS OFF"
)




# Vulkan
message(STATUS "Checking Vulkan path: $ENV{VULKAN_SDK}")

find_package(Vulkan REQUIRED)

target_link_libraries(NGIN PUBLIC
        #  SDL2::SDL2
        # SDL2::SDL2main
        glm::glm
        Vulkan::Vulkan
        Vulkan::Headers
        SIMDString
)

# RTTI
if (NOT NGIN_ENABLE_RTTI)
    if (MSVC)
        target_compile_options(NGIN PUBLIC /GR-)
    else ()
        target_compile_options(NGIN PUBLIC -fno-rtti)
    endif ()
endif ()


set_target_properties(NGIN PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        PREFIX ""
)

# Post-build command to copy SDL2 DLLs
#add_custom_command(TARGET NGIN POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#       $<TARGET_FILE:SDL2::SDL2>
#       $<TARGET_FILE_DIR:NGIN>
#)

# If SDL2main is a separate DLL, copy it as well
#add_custom_command(TARGET NGIN POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different
#       $<TARGET_FILE:SDL2::SDL2main>
#        $<TARGET_FILE_DIR:NGIN>
#)

add_library(NGIN::NGIN ALIAS NGIN)