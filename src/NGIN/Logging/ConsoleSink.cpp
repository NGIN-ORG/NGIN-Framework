#include <NGIN/Logging/ConsoleSink.hpp>

namespace NGIN::Logging
{
    void ConsoleSink::Initialize()
    {
#ifdef NGIN_PLATFORM_WINDOWS
        isTerminal = (void*) GetStdHandle(STD_OUTPUT_HANDLE);
#else
        isTerminal = isatty(fileno(stdout));
#endif
    }

    void ConsoleSink::Log(Entry message)
    {
        SetColor(message.level);
        std::cout << message.message << "\n";
        ResetColor();
    }
}// namespace NGIN::Logging