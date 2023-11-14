#include <memory>

namespace NGIN
{
    template<typename T>
    using Ticket = std::weak_ptr<T>;

    //MakeWeakRef
    template<typename T, typename... Args>
    Ticket<T> CreateTicket(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

}// namespace NGIN