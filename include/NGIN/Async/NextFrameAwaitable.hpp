#pragma once
#include <NGIN/Common/Types/Primitive.hpp>
#include <NGIN/Async/IAwaitable.hpp>
#include <coroutine>
namespace NGIN::Async
{
    struct NextTickAwaitable : public IAwaitable
    {
        Bool await_ready() const noexcept override
        {
            return false;
        }

        Void await_suspend(std::coroutine_handle<> handle) const noexcept override
        {
            ///TODO: Schedule the coroutine to run on the next frame        
        }
        
        Void await_resume() const noexcept override {}
    };
}// namespace NGIN::Async