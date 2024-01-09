#include <coroutine>
#include <exception>
#include <optional>
namespace NGIN::Async
{
template<typename T>
class Task {
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type {
        Task get_return_object() {
            return Task(handle_type::from_promise(*this));
        }

        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        template<typename U>
        requires (!std::is_void_v<T>)
        void return_value(U&& value) noexcept(std::is_nothrow_convertible_v<U, T>) {
            result = std::forward<U>(value);
        }

        void unhandled_exception() noexcept {
            exception = std::current_exception();
        }

        // Specialization for void
       // void return_void() noexcept requires (std::is_void_v<T>) {}

        T result{};
        std::exception_ptr exception;
    };

    Task(handle_type handle) : m_handle(handle) {}
    ~Task() {
        if (m_handle) m_handle.destroy();
    }

    // Deleted copy constructor and copy assignment operator
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    // Move constructor and move assignment operator
    Task(Task&& other) noexcept : m_handle(other.m_handle) {
        other.m_handle = nullptr;
    }

    Task& operator=(Task&& other) noexcept {
        if (this != &other) {
            if (m_handle) m_handle.destroy();
            m_handle = other.m_handle;
            other.m_handle = nullptr;
        }
        return *this;
    }

    // Retrieve the result of the coroutine
    T get() {
        if (exception) {
            std::rethrow_exception(exception);
        }
        return result;
    }

    // Wait for the coroutine to finish
    void wait() {
        if (!m_handle.done()) {
            m_handle.resume();
        }
        if (exception) {
            std::rethrow_exception(exception);
        }
    }

private:
    handle_type m_handle;
    T result;
    std::exception_ptr exception;
};


}
