#include <coroutine>
#include <exception>
#include <optional>
#include <future>
namespace NGIN::Async
{

    template<typename T>
    struct Task;

    template<typename T>
    struct TaskPromise
    {
        std::coroutine_handle<> continuation;
        T value;

        Task<T> get_return_object()
        {
            return Task<T> {std::coroutine_handle<TaskPromise<T>>::from_promise(*this)};
        };

        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        void return_value(T v) { value = v; }
        void unhandled_exception() { std::exit(1); }
    };
    template<typename T>
    struct Task
    {
        using promise_type = TaskPromise<T>;
        std::coroutine_handle<promise_type> coro;

        Task(std::coroutine_handle<promise_type> h) : coro(h) {}
        ~Task()
        {
            if (coro) coro.destroy();
        }

        T get()
        {
            if (coro)
            {
                coro.resume();
                return coro.promise().value;
            }
            throw std::runtime_error("Task not valid");
        }
    };

}// namespace NGIN::Async
