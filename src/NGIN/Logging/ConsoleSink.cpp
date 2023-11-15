#include <NGIN/Logging/ConsoleSink.hpp>
#ifdef NGIN_PLATFORM_WINDOWS
#include <windows.h>
#endif

namespace NGIN::Logging
{
    Bool ConsoleSink::Initialize()
    {
#ifdef NGIN_PLATFORM_WINDOWS
        DWORD temp;
        isTerminal = (Bool) GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &temp);
#else
        isTerminal = isatty(fileno(stdout));
#endif

        return isTerminal;
    }

    void ConsoleSink::Log(eLogLevel level, const String& message)
    {
        if (!isTerminal) [[unlikely]]
            return;
        SetColor(level);
        std::cout << message << "\n";
        ResetColor();
    }

    void ConsoleSink::Flush()
    {
        std::cout.flush();
    }

    void ConsoleSink::Shutdown() {}

    void ConsoleSink::SetColor(eLogLevel level)
    {
        switch (level)
        {
            case eLogLevel::Trace:
                std::cout << "\033[90m";// Dark gray for Trace
                break;
            case eLogLevel::Info:
                std::cout << "\033[32m";// Green for Info
                break;
            case eLogLevel::Debug:
                std::cout << "\033[36m";// Cyan for Debug
                break;
            case eLogLevel::Warning:
                std::cout << "\033[93m";// Bright yellow for Warning
                break;
            case eLogLevel::Error:
                std::cout << "\033[38;5;208m";// Orange for Error
                break;
            case eLogLevel::Critical:
                std::cout << "\033[91m";// Bright red for Critical
                break;
            default:
                std::cout << "\033[37m";// White for default
                break;
        }
    }

    void ConsoleSink::ResetColor()
    {
        std::cout << "\033[0m";
    }
}// namespace NGIN::Logging