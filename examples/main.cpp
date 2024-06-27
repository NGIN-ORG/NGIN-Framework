
#include <NGIN/IO/FileSystem.hpp>
#include <NGIN/IO/Path.hpp>
#include <NGIN/Types/Primitives.hpp>
#include <NGIN/Types/String.hpp>
#include <direct.h>// _getcwd
#include <filesystem>
#include <windows.h>


struct Temp : public NGIN::Stringifiable
{
    NGIN::String ToString() const override
    {
        return "Temp ☺ 字😂";
    }
};


/// @brief test
///
struct Foo
{
};

int main()
{


    SetConsoleOutputCP(CP_UTF8);

    NGIN::IO::Path path("F:\\Projects\\NGIN-Framework/CMakeLists.txt");
    NGIN::IO::Path path2("F:\\Projects\\NGIN-Framework/../.gitignore");
    NGIN::IO::Path path3("F:\\Projects\\NGIN-Framework/docs/");
    path.Normalize();
    path2.Normalize();
    path3.Normalize();
    std::cout << path.ToString() << NGIN::IO::FileSystem::Exists(path) << std::endl;
    std::cout << path2.ToString() << NGIN::IO::FileSystem::Exists(path2) << std::endl;
    std::cout << path3.ToString() << NGIN::IO::FileSystem::Exists(path3) << std::endl;


    return 0;
}