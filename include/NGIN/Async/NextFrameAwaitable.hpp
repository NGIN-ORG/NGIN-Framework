#pragma once
#include <NGIN/Common/Types/Primitive.hpp>
#include <coroutine>
namespace NGIN::Async
{
    struct NextTickAwaitable
    {
        Bool await_ready() const noexcept
        {
            return false;
        }

        Void await_suspend(std::coroutine_handle<> handle) const noexcept
        {
                }
        Void await_resume() const noexcept {}
    };
}// namespace NGIN::Async