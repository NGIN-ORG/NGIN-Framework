#pragma once
#include <NGIN/Common/Types/Primitive.hpp>
#include <NGIN/Async/IAwaitable.hpp>
#include <coroutine>
namespace NGIN::Async
{
    struct TimeDelaySecondsAwaitable : public IAwaitable
    {
        explicit TimeDelaySecondsAwaitable(F32 seconds) noexcept
            : seconds(seconds)
        {
        }

        Bool await_ready() const noexcept override
        {
            return false;
        }

        Void await_suspend(std::coroutine_handle<> handle) const noexcept override
        {
            ///TODO: Schedule the coroutine 
        }
        Void await_resume() const noexcept {} override

        F32 seconds;
    };
}// namespace NGIN::Async