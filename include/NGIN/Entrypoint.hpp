#pragma once
#include <exception>
#include <iostream>

extern int NGINMain(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    try
    {
        std::cout << "Hello, World! FROM NGIN" << std::endl;
        return NGINMain(argc, argv);
    } catch (std::exception ex)
    {
        std::cerr << "NGIN Exception: " << ex.what() << std::endl;
        return -1;
    }
}

// Redefine main to avoid conflicts with SDL
#undef main
#define main NGINMain