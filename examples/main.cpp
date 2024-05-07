
#include <NGIN/Types/Primitives.hpp>
#include <NGIN/Types/String.hpp>
#include <direct.h> // _getcwd

#include <filesystem>
using namespace NGIN::Memory;


int main()
{
    char* buffer = nullptr;
    buffer       = _getcwd(nullptr, 0);
    std::cout << std::filesystem::current_path() << std::endl;
    std::cout << buffer << std::endl;
    return 0;
}