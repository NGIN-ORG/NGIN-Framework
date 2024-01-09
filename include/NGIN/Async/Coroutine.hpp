#include <coroutine>
#include <exception>
#include <optional>
#include <future>

namespace NGIN::Async
{

    struct CoroutinePromise;

    // Coroutine type
    class Coroutine
    {
    public:
        using promise_type = CoroutinePromise;

        Coroutine(std::coroutine_handle<promise_type> h) : handle(h) {}
        ~Coroutine()
        {
            if (handle && !handle.done())
                handle.destroy();
        }

        Coroutine(const Coroutine&) = delete;
        Coroutine& operator=(const Coroutine&) = delete;
        Coroutine(Coroutine&&) = default;
        Coroutine& operator=(Coroutine&&) = default;

        bool IsDone() const { return handle.done(); }
        void Resume() const { handle.resume(); }

    private:
        std::coroutine_handle<promise_type> handle;
    };

    struct CoroutinePromise
    {
        Coroutine get_return_object()
        {
            return Coroutine {std::coroutine_handle<CoroutinePromise>::from_promise(*this)};
        }

        std::suspend_never initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        void return_void() {}
        void unhandled_exception() {}
    };

}// namespace NGIN::Async
