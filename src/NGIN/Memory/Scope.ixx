

export module NGIN.Memory:Scope;
import std;

namespace NGIN
{
    export template<typename T>
    using Scope = std::shared_ptr<T>;

    export template<typename T, typename... Args>
    Scope<T> CreateScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}// namespace NGIN