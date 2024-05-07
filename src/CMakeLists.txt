

include(${CMAKE_SOURCE_DIR}/include/CMakeHeaders.cmake)
include(${CMAKE_SOURCE_DIR}/src/CMakeSources.cmake)


# Determine library type
if (NGIN_BUILD_SHARED)
    set(NGIN_BUILD_TYPE SHARED)
else ()
    set(NGIN_BUILD_TYPE STATIC)
endif ()

add_library(NGIN ${NGIN_BUILD_TYPE})

if (NGIN_BUILD_SHARED)
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

include(CMakeDependencies.cmake)

target_link_libraries(NGIN PUBLIC
        #  SDL2::SDL2
        # SDL2::SDL2main
        glm::glm
        Vulkan::Vulkan
        Vulkan::Headers
        SIMDString
)

target_include_directories(NGIN PUBLIC
        ${RapidJSON_SOURCE_DIR}/include
)

target_link_libraries(NGIN PUBLIC

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