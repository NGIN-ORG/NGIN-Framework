#pragma once
#include <iostream>

extern int NGINMain(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    std::cout << "Hello, World! FROM NGIN" << std::endl;
    return NGINMain(argc, argv);
}

// Redefine main to avoid conflicts with SDL
#undef main
#define main NGINMain