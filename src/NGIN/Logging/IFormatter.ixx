
export module NGIN.Logging:IFormatter;

export import NGIN.Types;
import :LogLevel;
import std;

namespace NGIN::Logging
{
    /// @brief Interface for log formatters
    /// @todo Add documentation
    export class IFormatter
    {
    public:
        virtual ~IFormatter() = default;
        virtual String Format(LogLevel level, const String& message, const std::source_location& source = std::source_location::current()) = 0;
    };  
}// namespace NGIN::Logging
