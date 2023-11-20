
#ifdef NGIN_DEFINE_MAIN
#include <SDL2/SDL.h>
#include <iostream>

extern int NGINMain(int argc, char* argv[]);

int main(int argc, char* argv[])
{
#ifdef NGIN_ENABLE_EXCEPTIONS
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
    std::cout << "Hello, World! FROM NGIN" << std::endl;
    return NGINMain(argc, argv);
#endif
}
#endif