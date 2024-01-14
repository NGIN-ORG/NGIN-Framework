
#include <NGIN/Containers/StaticRingBuffer.hpp>
#include <NGIN/Entrypoint.hpp>
#include <NGIN/Logging/ConsoleSink.hpp>
#include <NGIN/Logging/SimpleFormatter.hpp>
#include <NGIN/Logging/SimpleLogger.hpp>
#include <NGIN/System/Info.hpp>
#include <NGIN/Util/Format.hpp>
#include <iostream>
#include <coroutine>
#include <NGIN/Async/Coroutine.hpp>
#include <NGIN/Async/NextFrameAwaitable.hpp>
#include <NGIN/Async/Task.hpp>
#include <future>
using NGIN::Containers::StaticRingBuffer;

NGIN::Async::Coroutine exampleCoroutine()
{
    std::cout << "Coroutine started" << std::endl;
    co_await NGIN::Async::NextTickAwaitable(2);
    std::cout << "Coroutine resumed" << std::endl;
    co_return;
}

NGIN::Async::Coroutine OtherCoroutine()
{
    std::cout << "Coroutine started" << std::endl;
    co_await NGIN::Async::NextTickAwaitable(2);
    std::cout << "Coroutine resumed" << std::endl;
    co_return;
}


int main(int argc, char* argv[])
{
    using Logger = NGIN::Logging::SimpleLogger<NGIN::Logging::SimpleFormatter>;
    Logger logger;
    logger.AddSink<NGIN::Logging::ConsoleSink>();
    logger.Initialize();
    logger.Log(NGIN::Logging::eLogLevel::Trace, std::source_location::current(), "Hello, World!");


    auto a = exampleCoroutine();
    auto b = OtherCoroutine();


    NGIN::Async::TickScheduler::GetInstance().Tick();
    NGIN::Async::TickScheduler::GetInstance().Tick();
    NGIN::Async::TickScheduler::GetInstance().Tick();

    std::cout << "Coroutine done: " << a.IsDone() << std::endl;

    logger.Flush();
    logger.Shutdown();

    return 0;
}