#pragma once
#include <NGIN/Common/Types/Primitive.hpp>
namespace NGIN::Async
{
    struct IAwaitable
    {
        virtual ~IAwaitable() = default;

        virtual Bool await_ready() const noexcept = 0;
        virtual Void await_suspend(std::coroutine_handle<> handle) const noexcept = 0;
        virtual Void await_resume() const noexcept = 0;
    };
}