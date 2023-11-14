#include <memory>

namespace NGIN
{
    template<typename T>
    using Ref = std::shared_ptr<T>;

    //MakeRef
    template<typename T, typename... Args>
    Ref<T> CreateRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}// namespace NGIN