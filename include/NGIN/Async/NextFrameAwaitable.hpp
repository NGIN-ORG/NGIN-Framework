#pragma once
#include <NGIN/Common/Types/Primitive.hpp>
#include <NGIN/Async/IAwaitable.hpp>
#include <coroutine>
namespace NGIN::Async
{
    struct NextTickAwaitable
    {

        explicit NextTickAwaitable(float numberOfTicks)
            : ticksLeft(numberOfTicks) {}

        UInt32 ticksLeft;

        Bool await_ready() const noexcept
        {
            return ticksLeft == 0;
        }

        Void await_suspend(std::coroutine_handle<> handle) const noexcept
        {
            ///TODO: Schedule the coroutine to run on the next frame
        }

        Void await_resume() noexcept { --ticksLeft; }
    };
}// namespace NGIN::Async