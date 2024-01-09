#pragma once
#include <NGIN/Common/Types/Primitive.hpp>
#include <NGIN/Async/IAwaitable.hpp>
#include <coroutine>
#include <iostream>
namespace NGIN::Async
{
    class TimeDelaySecondsAwaitable
    {
    public:
        explicit TimeDelaySecondsAwaitable(float delaySeconds)
            : m_delaySeconds(delaySeconds) {}

        // Check if the delay is already elapsed
        bool await_ready() const
        {
            return m_delaySeconds <= 0;
        }

        // Suspend the coroutine and set a timer to resume it
        void await_suspend(std::coroutine_handle<> handle)
        {
            std::thread([=]() {
                std::this_thread::sleep_for(std::chrono::duration<float>(m_delaySeconds));
                handle.resume();
            }).detach();
        }

        // What to do when resuming the coroutine - in this case, nothing
        void await_resume() const {}

    private:
        float m_delaySeconds;
    };

}// namespace NGIN::Async