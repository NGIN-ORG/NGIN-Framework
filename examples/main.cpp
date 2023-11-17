
#include <NGIN/Entrypoint.hpp>
#include <NGIN/Logging/ConsoleSink.hpp>
#include <NGIN/Logging/SimpleFormatter.hpp>
#include <NGIN/Logging/SimpleLogger.hpp>
#include <NGIN/System/Info.hpp>
#include <NGIN/Util/Format.hpp>
#include <iostream>
int main(int argc, char* argv[])
{
    using Logger = NGIN::Logging::SimpleLogger<NGIN::Logging::SimpleFormatter>;
    Logger logger;
    logger.AddSink<NGIN::Logging::ConsoleSink>();
    logger.AddSink<NGIN::Logging::ConsoleSink>();
    logger.Initialize();
    logger.Log(NGIN::Logging::eLogLevel::Trace, std::source_location::current(), "Hello, World!");
    logger.Log(NGIN::Logging::eLogLevel::Info, std::source_location::current(), "Hello, World!");
    logger.Log(NGIN::Logging::eLogLevel::Debug, std::source_location::current(), "Hello, World!");
    logger.Log(NGIN::Logging::eLogLevel::Warning, std::source_location::current(), "Hello, World!");
    logger.Log(NGIN::Logging::eLogLevel::Error, std::source_location::current(), "Hello, World!");
    logger.Log(NGIN::Logging::eLogLevel::Critical, std::source_location::current(), "Hello, World!");

    logger.Flush();
    logger.Shutdown();

    NGIN::System::Info info = NGIN::System::GetSystemInfo();

    return 0;
}