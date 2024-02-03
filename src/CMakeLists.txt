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
 "NGIN/NGIN.ixx"  
 "NGIN/Util/Format.ixx" 
 "NGIN/Types/Primitives.ixx" 
 "NGIN/Types/String.ixx" 
 "NGIN/Types/Types.ixx" 
 "NGIN/Util/Util.ixx" 
 "NGIN/Containers/Vector.ixx" 
 "NGIN/Containers/Array.ixx" 
 "NGIN/Containers/Deque.ixx" 
 "NGIN/Containers/Map.ixx" 
 "NGIN/Containers/UnorderedMap.ixx" 
 "NGIN/Containers/Containers.ixx" 
 "NGIN/Memory/Ref.ixx" 
 "NGIN/Memory/Scope.ixx" 
 "NGIN/Memory/Ticket.ixx" 
 "NGIN/Memory/Memory.ixx" 
 "NGIN/Logging/LogLevel.ixx" 
 "NGIN/Meta/EnumTraits.ixx" 
 "NGIN/Meta/Meta.ixx" 
 "NGIN/Logging/Logging.ixx"  
 "NGIN/Logging/ILogger.ixx" 
 "NGIN/Logging/IFormatter.ixx"
 "NGIN/Logging/ISink.ixx"
 "NGIN/Util/StringUtil.ixx"
 "NGIN/Logging/SimpleFormatter.ixx"  
 "NGIN/Util/TimeUtil.ixx" 
 "NGIN/Logging/SimpleLogger.ixx" 
 "NGIN/Logging/ConsoleSink.ixx" "NGIN/Meta/FunctionTraits.ixx" "NGIN/Meta/TypeInfo.ixx" "NGIN/Reflection/IReflectable.ixx" "NGIN/Reflection/Reflection.ixx" "NGIN/Reflection/Registry.ixx" "NGIN/Types/Optional.ixx")

target_sources(NGIN PRIVATE
    
)




include(CMakeDependencies.cmake)

target_link_libraries(NGIN PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    glm::glm
    Vulkan::Vulkan
    Vulkan::Headers
)

if(NOT NGIN_ENABLE_RTTI)
    if(MSVC)
        target_compile_options(NGIN PUBLIC /GR-)
    else()
        target_compile_options(NGIN PUBLIC -fno-rtti)
    endif()
endif()
if(NOT NGIN_ENABLE_EXCEPTIONS)
    if(MSVC)
        target_compile_options(NGIN PUBLIC /EHsc)
        target_compile_definitions(NGIN PUBLIC _HAS_EXCEPTIONS=0)
    else()
        target_compile_options(NGIN PUBLIC -fno-exceptions)
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