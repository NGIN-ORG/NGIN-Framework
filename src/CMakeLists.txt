if(NGIN_BUILD_SHARED)
    set(NGIN_BUILD_TYPE SHARED)
else()
    set(NGIN_BUILD_TYPE STATIC)
endif()

add_library(NGIN ${NGIN_BUILD_TYPE}
    "main.cpp"
    "NGIN/Logging/ConsoleSink.cpp"
    "NGIN/Util/UUID.cpp"
)

target_include_directories(NGIN
    PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
        $<INSTALL_INTERFACE:include>
)

include(CMakeDependencies.cmake)

target_link_libraries(NGIN PUBLIC
    fmt::fmt
    SDL2::SDL2
    SDL2::SDL2main
    glm
    Vulkan::Vulkan
    Vulkan::Headers
)

if(MSVC)
    target_compile_options(NGIN PRIVATE /GR-)
else()
    target_compile_options(NGIN PRIVATE -fno-rtti)
endif()

if(MSVC)
    target_compile_options(NGIN PRIVATE /EHsc-)
else()
    target_compile_options(NGIN PRIVATE -fno-exceptions)
endif()

# Post-build command to copy SDL2 DLLs
add_custom_command(TARGET NGIN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE_DIR:NGIN>
)

# If SDL2main is a separate DLL, copy it as well
add_custom_command(TARGET NGIN POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2main>
        $<TARGET_FILE_DIR:NGIN>
)

add_library(NGIN::Framework ALIAS NGIN)