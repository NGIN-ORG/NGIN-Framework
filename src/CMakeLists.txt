if(NGIN_BUILD_SHARED)
    set(NGIN_BUILD_TYPE SHARED)
else()
    set(NGIN_BUILD_TYPE STATIC)
endif()

add_library(NGIN ${NGIN_BUILD_TYPE}
    "test.cpp"
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

add_library(NGIN::Framework ALIAS NGIN)