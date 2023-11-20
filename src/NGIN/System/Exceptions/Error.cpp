#include <NGIN/System/Exceptions/Error.hpp>

namespace NGIN::System::Exceptions
{
    Error::Error(const std::string& message, const std::source_location& location)
        : std::runtime_error(message), location(location)
    {
    }


}// namespace NGIN::System::Exceptions