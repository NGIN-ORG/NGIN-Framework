if(NGIN_BUILD_SHARED)
    set(NGIN_BUILD_TYPE SHARED)
else()
    set(NGIN_BUILD_TYPE STATIC)
endif()

add_library(NGIN ${NGIN_BUILD_TYPE})

target_sources(NGIN PUBLIC 
    FILE_SET 
        ngin_module_interfaces 
    TYPE 
        CXX_MODULES
    BASE_DIRS 
        ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
        
 "NGIN/Logging/ILogger.ixx" "NGIN/Util/Format.ixx" "NGIN/Common/Types/Primitive.ixx" "NGIN/Common/Types/String.ixx" "NGIN/Common/Types.ixx" "NGIN/Util.ixx")

target_sources(NGIN PRIVATE
    
)




include(CMakeDependencies.cmake)

target_link_libraries(NGIN PRIVATE
    fmt::fmt
    SDL2::SDL2
    SDL2::SDL2main
    glm::glm
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

add_library(NGIN::NGIN ALIAS NGIN)