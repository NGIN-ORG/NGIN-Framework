add_executable(HelloWorld ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(HelloWorld PRIVATE NGIN)

