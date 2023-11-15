
#include <NGIN/Entrypoint.hpp>
#include <NGIN/Logging/ConsoleSink.hpp>
#include <NGIN/System/Info.hpp>
#include <NGIN/Util/Format.hpp>
#include <iostream>
int main(int argc, char* argv[])
{

    NGIN::Logging::ConsoleSink sink;
    sink.Initialize();
    sink.Log(NGIN::Logging::eLogLevel::Trace, "Hello, World!");

    sink.Log(NGIN::Logging::eLogLevel::Info, "Hello, World!");
    sink.Log(NGIN::Logging::eLogLevel::Debug, "Hello, World!");

    sink.Log(NGIN::Logging::eLogLevel::Warning, "Hello, World!");
    sink.Log(NGIN::Logging::eLogLevel::Error, "Hello, World!");
    sink.Log(NGIN::Logging::eLogLevel::Critical, "Hello, World!");

    sink.Flush();

    NGIN::System::Info info = NGIN::System::GetSystemInfo();
    sink.Log(NGIN::Logging::eLogLevel::Info, info.ToString());

    return 0;
}