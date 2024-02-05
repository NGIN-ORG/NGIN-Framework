
export module NGIN.Memory:Ref;
import std;

namespace NGIN
{
    export template<typename T>
    using Ref = std::shared_ptr<T>;

    export template<typename T, typename... Args>
    Ref<T> CreateRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}