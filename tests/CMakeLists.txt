include(${CMAKE_SOURCE_DIR}/CMakeUtils.cmake)

FETCH_LIBRARY(
        NAME ut
        GIT_REPOSITORY "https://github.com/NGIN-ORG/ut"
        GIT_TAG "master"
        OPTIONS
        "BOOST_UT_DISABLE_MODULE ON"
        "BOOST_UT_BUILD_EXAMPLES OFF"
        "BOOST_UT_BUILD_TESTS OFF"
)

add_executable(NGIN_TESTS
        "main.cpp"
        "NGIN/Memory/FreeListAllocator.cpp"
        "NGIN/Meta/FunctionTraits.cpp"
        "NGIN/Meta/TypeInfo.cpp"
        "NGIN/Serialization/JSON/JSONLexer.cpp"
 "NGIN/IO/Path.cpp")


target_link_libraries(NGIN_TESTS PRIVATE Boost::ut NGIN::NGIN)

add_test(NAME NGIN_TESTS COMMAND NGIN_TESTS)
#copy NGIN dll to binary dir
#add_custom_command(TARGET NGIN_TESTS POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
#                   $<TARGET_FILE:NGIN>
#                   $<TARGET_FILE_DIR:NGIN_TESTS>)

#If debug run test automatically, useful for in editor view
#if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#   add_custom_command(TARGET NGIN_TESTS
#                       POST_BUILD
#                       COMMAND $<TARGET_FILE:NGIN_TESTS>)
#endif()