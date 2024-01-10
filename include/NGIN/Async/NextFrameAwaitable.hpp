#pragma once
#include <NGIN/Common/Types/Primitive.hpp>
#include <NGIN/Async/IAwaitable.hpp>
#include <coroutine>
#include <vector>
#include <utility>
namespace NGIN::Async
{

    struct TickScheduler
    {
        std::vector<std::pair<std::coroutine_handle<>, UInt32>> tasks;

        static TickScheduler& GetInstance()
        {
            static TickScheduler instance;
            return instance;
        }

        void Schedule(std::coroutine_handle<> handle, UInt32 ticks)
        {
            for (auto& task: tasks)
            {
                if (task.first == nullptr)
                {
                    task.first = handle;
                    task.second = ticks;
                    return;
                }
            }
            tasks.emplace_back(handle, ticks);
        }
        void Tick()
        {
            for (auto& task: tasks)
            {
                if (task.first == nullptr)
                    continue;
                if (task.first.done())
                    continue;

                if (task.second > 0)
                    --task.second;
                else
                {
                    task.first.resume();
                    task.first = nullptr;
                }
            }
        }

    protected:
        TickScheduler() = default;
    };
    struct NextTickAwaitable
    {

        explicit NextTickAwaitable(float numberOfTicks)
            : ticks(numberOfTicks) {}

        UInt32 ticks = 0;

        Bool await_ready() const noexcept
        {
            return ticks == 0;
        }

        Void await_suspend(std::coroutine_handle<> handle) noexcept
        {
            if (ticks > 0)
                TickScheduler::GetInstance().Schedule(handle, ticks);
        }

        Void await_resume() const noexcept {}
    };
}// namespace NGIN::Async