set(NGIN_SYSTEM_SRC
    "NGIN/System/Exceptions/Error.cpp"
)
if(WIN32)
    list(APPEND NGIN_SYSTEM_SRC "NGIN/System/Platform/Windows/Info.cpp")
else()
    list(APPEND NGIN_SYSTEM_SRC "NGIN/System/Platform/Unix/Info.cpp")
endif()

set(NGIN_LOGGING_SRC
    "NGIN/Logging/ConsoleSink.cpp"
    "NGIN/Logging/ErrorSink.cpp"
    "NGIN/Logging/SimpleFormatter.cpp"
)

set(NGIN_MEMORY_SRC
    "NGIN/Memory/Mallocator.cpp"
    "NGIN/Memory/LinearAllocator.cpp"
)

set(NGIN_UTIL_SRC
    "NGIN/Util/UUID.cpp"
)

set(NGIN_PLATFORM_WINDOWS_SRC
    "NGIN/Platform/Windows/SEH.cpp"
)
if(NGIN_PLATFORM_WINDOWS)
    list(APPEND NGIN_PLATFORM_WINDOWS_SRC "NGIN/Platform/Windows/SEH.cpp")
endif()

if(NGIN_BUILD_SHARED)
    set(NGIN_BUILD_TYPE SHARED)
else()
    set(NGIN_BUILD_TYPE STATIC)
endif()

add_library(NGIN ${NGIN_BUILD_TYPE}
    "main.cpp"
    ${NGIN_SYSTEM_SRC}
    ${NGIN_LOGGING_SRC}
    ${NGIN_MEMORY_SRC}
    ${NGIN_UTIL_SRC}
    ${NGIN_PLATFORM_WINDOWS_SRC}
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

if(NOT NGIN_ENABLE_RTTI)
    if(MSVC)
        target_compile_options(NGIN PRIVATE /GR-)
    else()
        target_compile_options(NGIN PRIVATE -fno-rtti)
    endif()
endif()
if(NOT NGIN_ENABLE_EXCEPTIONS)
    if(MSVC)
        target_compile_options(NGIN PRIVATE /EHsc-)
    else()
        target_compile_options(NGIN PRIVATE -fno-exceptions)
    endif()
endif()

set_target_properties(NGIN PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
    PREFIX ""
)

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