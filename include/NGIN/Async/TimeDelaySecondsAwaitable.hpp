#pragma once
#include <NGIN/Common/Types/Primitive.hpp>
#include <coroutine>
namespace NGIN::Async
{
    struct TimeDelaySecondsAwaitable
    {
        explicit TimeDelaySecondsAwaitable(Float seconds) noexcept
            : seconds(seconds)
        {
        }

        Bool await_ready() const noexcept
        {
            return false;
        }

        Void await_suspend(std::coroutine_handle<> handle) const noexcept
        {
            ///TODO: Schedule the coroutine 
        }
        Void await_resume() const noexcept {}

        Float seconds;
    };
}// namespace NGIN::Async