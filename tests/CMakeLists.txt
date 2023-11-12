FetchContent_Declare(googletest 
    GIT_REPOSITORY "https://github.com/google/googletest"
    GIT_TAG "main"
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)

macro(ngin_add_test TARGET_NAME TEST_NAME)
    add_executable(${TEST_NAME} ${ARGN})
    target_compile_definitions(${TARGET_NAME} PRIVATE -DNGIN_TESTING)
    target_link_libraries(${TEST_NAME} PRIVATE ngin gtest_main)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endmacro()