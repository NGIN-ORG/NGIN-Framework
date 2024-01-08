
#include <NGIN/Containers/StaticRingBuffer.hpp>
#include <NGIN/Entrypoint.hpp>
#include <NGIN/Logging/ConsoleSink.hpp>
#include <NGIN/Logging/SimpleFormatter.hpp>
#include <NGIN/Logging/SimpleLogger.hpp>
#include <NGIN/System/Info.hpp>
#include <NGIN/Util/Format.hpp>
#include <iostream>
#include <coroutine>
#include <NGIN/Async/TimeDelaySecondsAwaitable.hpp>

using NGIN::Containers::StaticRingBuffer;

task<void> Foo ()
{
    co_await NGIN::Async::TimeDelaySecondsAwaitable(1.0f);
    std::cout << "Hello, World!" << std::endl;
}

int main(int argc, char* argv[])
{
    using Logger = NGIN::Logging::SimpleLogger<NGIN::Logging::SimpleFormatter>;
    Logger logger;
    logger.AddSink<NGIN::Logging::ConsoleSink>();
    logger.Initialize();
    logger.Log(NGIN::Logging::eLogLevel::Trace, std::source_location::current(), "Hello, World!");
    logger.Log(NGIN::Logging::eLogLevel::Info, std::source_location::current(), "Hello, World!");
    logger.Log(NGIN::Logging::eLogLevel::Debug, std::source_location::current(), "Hello, World!");
    logger.Log(NGIN::Logging::eLogLevel::Warning, std::source_location::current(), "Hello, World!");
    logger.Log(NGIN::Logging::eLogLevel::Error, std::source_location::current(), "Hello, World!");
    logger.Log(NGIN::Logging::eLogLevel::Critical, std::source_location::current(), "Hello, World!");
    StaticRingBuffer<int, 10> buffer;
    for (size_t i = 0; i < 10; i++)
    {
        buffer.Push(i + 1);
    }

    for (int i = 0; i < 10; i++)
    {
        buffer.Pop();
    }

    for (size_t i = 0; i < 5; i++)
    {
        buffer.Push(i + 1);
    }


    logger.Log(NGIN::Logging::eLogLevel::Info, std::source_location::current(), "For each");

    for (int i: buffer)
    {
        logger.Log(NGIN::Logging::eLogLevel::Info, std::source_location::current(), "Buffer: {}", i);
    }

    logger.Log(NGIN::Logging::eLogLevel::Info, std::source_location::current(), "POP");

    while (!buffer.IsEmpty())
    {
        logger.Log(NGIN::Logging::eLogLevel::Info, std::source_location::current(), "Buffer: {}", buffer.Pop());
    }


    logger.Flush();
    logger.Shutdown();


    return 0;
}