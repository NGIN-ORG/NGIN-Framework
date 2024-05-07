
# Define test sources

add_executable(NGIN_TESTS
        "main.cpp"
        "NGIN/Memory/FreeListAllocator.cpp"
        "NGIN/Meta/FunctionTraits.cpp"
        "NGIN/Meta/TypeInfo.cpp"
        "NGIN/Serialization/JSON/JSONLexer.cpp"
)


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