#pragma once
#include <NGIN/Common/Types/Primitive.hpp>
#include <NGIN/Async/IAwaitable.hpp>
#include <coroutine>
#include <iostream>
namespace NGIN::Async
{
    class TimeDelaySecondsAwaitable {
    public:
        explicit TimeDelaySecondsAwaitable(int delaySeconds) : m_delaySeconds(delaySeconds) {}

        bool await_ready() const noexcept {
            std::cout << "await_ready" << std::endl;
            return m_delaySeconds <= 0;
        }

        void await_suspend(std::coroutine_handle<> handle) const {
            std::cout << "await_suspend" << std::endl;
            std::thread([handle, this] {
                std::this_thread::sleep_for(std::chrono::seconds(m_delaySeconds));
                handle.resume();
            }).detach();
        }

        void await_resume() const noexcept {std::cout << "await_resume" << std::endl;}

    private:
        int m_delaySeconds;
    };

}// namespace NGIN::Async