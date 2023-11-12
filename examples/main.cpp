#include <NGIN/Entrypoint.hpp>
#include <NGIN/Logging/Defines.hpp>
#include <NGIN/Meta/EnumTraits.hpp>
#include <iostream>
int main(int argc, char* argv[])
{
    std::cout << "Hello, World!" << std::endl;
    for (auto a: NGIN::Meta::EnumTraits<NGIN::Logging::eLogLevel>::values)
    {
        std::cout << NGIN::Meta::EnumTraits<NGIN::Logging::eLogLevel>::ToString(a) << std::endl;
    }
    return 0;
}