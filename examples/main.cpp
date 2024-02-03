
#include <iostream>
#include <source_location>

import NGIN.Logging;
import NGIN.IReflectable;

enum class TestEnum
{
    A,
    B,
    C
};

int main()
{
    using namespace NGIN;

    MyFunc();
    std::cout << "Hello World!" << std::endl;

    NGIN::Meta::EnumTraits<Logging::LogLevel> te = {};
    std::cout << te.ToString(Logging::LogLevel::Info) << std::endl;

    Logging::SimpleLogger<Logging::SimpleFormatter> logger = {};
    logger.AddSink<Logging::ConsoleSink>();


    logger.Log(NGIN::Logging::LogLevel::Info, "Hey gal");
    logger.Log(NGIN::Logging::LogLevel::Debug, "Hey gal {}", 2);

   // NGIN::Util::Format("test {}", 2);
    return 0;
}
