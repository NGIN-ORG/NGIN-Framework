
export module NGIN.Memory:Ticket;
import std;

namespace NGIN
{
    export template<typename T>
    using Ticket = std::weak_ptr<T>;

    export template<typename T, typename... Args>
    Ticket<T> CreateTicket(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}// namespace NGIN