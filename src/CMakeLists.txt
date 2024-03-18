

# Define module file lists
set(NGIN_REFLECTION_FILES
        "NGIN/Reflection/IReflectable.ixx"
        "NGIN/Reflection/Reflection.ixx"
        "NGIN/Reflection/Registry.ixx"
)

set(NGIN_IO_FILES
        "NGIN/IO/Format.ixx"
        "NGIN/IO/IO.ixx"
)

set(NGIN_MEMORY_FILES
        "NGIN/Memory/Memory.ixx"
        "NGIN/Memory/Ref.ixx"
        "NGIN/Memory/Scope.ixx"
        "NGIN/Memory/Ticket.ixx"
        "NGIN/Memory/IAllocator.ixx"
        "NGIN/Memory/Mallocator.ixx"
        "NGIN/Memory/LinearAllocator.ixx"
        "NGIN/Memory/FreeListAllocator.ixx"
        "NGIN/Memory/AlignmentUtils.ixx"
)

set(NGIN_UTIL_FILES
        "NGIN/Util/Util.ixx"
        "NGIN/Util/StringUtil.ixx"
        "NGIN/Util/TimeUtil.ixx"
)

set(NGIN_CONTAINERS_FILES
        "NGIN/Containers/Vector.ixx"
        "NGIN/Containers/Array.ixx"
        "NGIN/Containers/Deque.ixx"
        "NGIN/Containers/Map.ixx"
        "NGIN/Containers/UnorderedMap.ixx"
        "NGIN/Containers/Containers.ixx"
)

set(NGIN_META_FILES
        "NGIN/Meta/EnumTraits.ixx"
        "NGIN/Meta/Meta.ixx"
        "NGIN/Meta/FunctionTraits.ixx"
        "NGIN/Meta/TypeInfo.ixx"
)

set(NGIN_TIME_FILES
        "NGIN/Time/Time.ixx"
        "NGIN/Time/Timer.ixx"
        "NGIN/Time/Units.ixx"
        "NGIN/Time/Ratio.ixx"
)

set(NGIN_UNITS_FILES
        "NGIN/Units/Units.ixx"
        "NGIN/Units/Ratio.ixx"
        "NGIN/Units/IUnit.ixx"
        "NGIN/Units/TimeUnits.ixx"
)

set(NGIN_TYPES_FILES
        "NGIN/Types/Primitives.ixx"
        "NGIN/Types/String.ixx"
        "NGIN/Types/Types.ixx"
)

set(NGIN_LOGGING_FILES
        "NGIN/Logging/LogLevel.ixx"
        "NGIN/Logging/Logging.ixx"
        "NGIN/Logging/ILogger.ixx"
        "NGIN/Logging/IFormatter.ixx"
        "NGIN/Logging/ISink.ixx"
        "NGIN/Logging/SimpleFormatter.ixx"
        "NGIN/Logging/SimpleLogger.ixx"
        "NGIN/Logging/ConsoleSink.ixx"
)
# Combine all module file lists
set(NGIN_ALL_MODULE_FILES
        ${NGIN_REFLECTION_FILES}
        ${NGIN_IO_FILES}
        ${NGIN_MEMORY_FILES}
        ${NGIN_UTIL_FILES}
        ${NGIN_CONTAINERS_FILES}
        ${NGIN_META_FILES}
        ${NGIN_TIME_FILES}
        ${NGIN_UNITS_FILES}
        ${NGIN_TYPES_FILES}
        ${NGIN_LOGGING_FILES}
        "NGIN/NGIN.ixx"
        "std.ixx"
        "std.compat.ixx"
        # Add other module file lists here...
)


# Determine library type
if (NGIN_BUILD_SHARED)
    set(NGIN_BUILD_TYPE SHARED)
else ()
    set(NGIN_BUILD_TYPE STATIC)
endif ()# Define the library target

add_library(NGIN ${NGIN_BUILD_TYPE}
)

target_sources(NGIN PUBLIC
        FILE_SET
        ngin_module_interfaces
        TYPE
        CXX_MODULES
        BASE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}
        FILES
        ${NGIN_ALL_MODULE_FILES}
)

target_sources(NGIN PRIVATE

)


include(CMakeDependencies.cmake)

target_link_libraries(NGIN PRIVATE
        #  SDL2::SDL2
        # SDL2::SDL2main
        glm::glm
        Vulkan::Vulkan
        Vulkan::Headers
        SIMDString

)

target_link_libraries(NGIN PUBLIC

)

if (NOT NGIN_ENABLE_RTTI)
    if (MSVC)
        target_compile_options(NGIN PUBLIC /GR-)
    else ()
        target_compile_options(NGIN PUBLIC -fno-rtti)
    endif ()
endif ()
if (MSVC)
    target_compile_options(NGIN PUBLIC /EHsc)
endif ()

# RTTI
if (NOT NGIN_ENABLE_RTTI)
    target_compile_options(NGIN PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/GR-> $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-fno-rtti>)
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