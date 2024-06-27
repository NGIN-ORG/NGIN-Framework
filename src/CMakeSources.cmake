

# Define module file lists
set(NGIN_REFLECTION_SRC_FILES

)

set(NGIN_IO_SRC_FILES
        "NGIN/IO/Path.cpp"
)

set(NGIN_MEMORY_SRC_FILES
        "NGIN/Memory/FreeListAllocator.cpp"
        "NGIN/Memory/Mallocator.cpp"
)

set(NGIN_UTIL_SRC_FILES

)

set(NGIN_CONTAINERS_SRC_FILES

)

set(NGIN_META_SRC_FILES

)

set(NGIN_TIME_SRC_FILES

)

set(NGIN_UNITS_SRC_FILES

)

set(NGIN_TYPES_SRC_FILES

)

set(NGIN_LOGGING_SRC_FILES

)

set(NGIN_MATH_SRC_FILES
)

set(NGIN_SERIALIZATION_SRC_FILES
        "NGIN/Serialization/JSON/JSONLexer.cpp"
        "NGIN/Serialization/JSON/JSONParser.cpp"
        "NGIN/Serialization/XML/XMLLexer.cpp"
)
if(WIN32)
set(NGIN_PLATFORM_SRC_FILES
    "NGIN/IO/Platform/Win32/FileSystem.cpp"
)
endif()

# Combine all module file lists
set(NGIN_ALL_SRC_FILES
        ${NGIN_REFLECTION_SRC_FILES}
        ${NGIN_IO_SRC_FILES}
        ${NGIN_MEMORY_SRC_FILES}
        ${NGIN_UTIL_SRC_FILES}
        ${NGIN_CONTAINERS_SRC_FILES}
        ${NGIN_META_SRC_FILES}
        ${NGIN_TIME_SRC_FILES}
        ${NGIN_UNITS_SRC_FILES}
        ${NGIN_TYPES_SRC_FILES}
        ${NGIN_LOGGING_SRC_FILES}
        ${NGIN_MATH_SRC_FILES}
        ${NGIN_SERIALIZATION_SRC_FILES}
        ${NGIN_PLATFORM_SRC_FILES}
        # Add other module file lists here...
)

