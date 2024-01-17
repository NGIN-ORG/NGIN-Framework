
#include <NGIN/Async/Coroutine.hpp>
#include <NGIN/Async/NextFrameAwaitable.hpp>
#include <NGIN/Async/Task.hpp>
#include <NGIN/Containers/StaticRingBuffer.hpp>
#include <NGIN/Entrypoint.hpp>
#include <NGIN/Logging/ConsoleSink.hpp>
#include <NGIN/Logging/SimpleFormatter.hpp>
#include <NGIN/Logging/SimpleLogger.hpp>
#include <NGIN/Math/Vector3.hpp>
#include <NGIN/Memory/Mallocator.hpp>
#include <NGIN/System/Info.hpp>
#include <NGIN/Time/Timer.hpp>
#include <NGIN/Util/Format.hpp>
#include <coroutine>
#include <future>
#include <glm/glm.hpp>
#include <iostream>
#include <thread>
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
    logger.Log(NGIN::Logging::LogLevel::Trace, std::source_location::current(), "Hello, World!");


    auto a = exampleCoroutine();
    auto b = OtherCoroutine();


    NGIN::Async::TickScheduler::GetInstance().Tick();
    NGIN::Async::TickScheduler::GetInstance().Tick();
    NGIN::Async::TickScheduler::GetInstance().Tick();

    int j = 0;
    std::cin >> j;

    NGIN::Time::Timer<NGIN::Time::SteadyClock> timer1 = {};

    glm::vec3 vec1 = {1, 2, 3};
    vec1 += j;
    glm::vec3 vec2 = {4, 5, 6};
    vec2 += j;
    for (volatile int i = 0; i < 10000; i++)
    {
        volatile glm::vec3 vec3 = glm::cross(vec1, vec2);
    }

    volatile auto time1 = timer1.ElapsedInt<NGIN::Time::Microseconds>();
    NGIN::Time::Timer<NGIN::Time::SteadyClock> timer2 = {};

    NGIN::Math::Vector3 vec11 = {1, 2, 3};
    vec11 += j;

    NGIN::Math::Vector3 vec21 = {4, 5, 6};
    vec21 += j;

    for (volatile int i = 0; i < 10000; i++)
    {
        volatile NGIN::Math::Vector3 result = NGIN::Math::Cross(vec11, vec21);
    }

    volatile auto time2 = timer2.ElapsedInt<NGIN::Time::Microseconds>();


    std::cout << "NGIN::Math::Vector3::Cross took " << time2 << " Microseconds" << '\n';
    std::cout << "glm::cross took " << time1 << " Microseconds" << '\n';


    std::cout
            << "Coroutine done: " << a.IsDone() << std::endl;

    logger.Flush();
    logger.Shutdown();

    return 0;
}