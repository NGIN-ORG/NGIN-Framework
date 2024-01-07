
#ifdef NGIN_DEFINE_MAIN
#ifdef NGIN_PLATFORM_WINDOWS
#include <NGIN/Platform/Windows/SEH.hpp>
#endif

#include <SDL2/SDL.h>
#include <iostream>
#include <thread>


std::thread::id mainThreadId = {};

extern int NGINMain(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    mainThreadId = std::this_thread::get_id();
#ifdef NGIN_PLATFORM_WINDOWS
    SetUnhandledExceptionFilter(NGIN::Platform::Windows::UnhandledExceptionHandler);
#endif


#ifndef NGIN_ENABLE_EXCEPTIONS
    try
    {
        std::cout << "Hello, World! FROM NGIN" << std::endl;
        return NGINMain(argc, argv);
    } catch (const std::exception& ex)
    {
        std::cerr << "NGIN Exception: " << ex.what() << std::endl;
        return -1;
    }
#else
    std::cout
            << "Hello, World! FROM NGIN no exception" << std::endl;
    std::thread t([]() {
        std::cout << "Hello, World! FROM NGIN thread" << std::endl;
        int b = 0;
        int a = 2 / b;
    });

    return NGINMain(argc, argv);
#endif
}
#endif