add_executable(HelloWorld
        main.cpp)

 set(NGIN_SHARED ON CACHE INTERNAL "Set by FETCH_LIBRARY")

target_link_libraries(HelloWorld PRIVATE NGIN)

