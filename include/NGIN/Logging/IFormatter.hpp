#pragma once

#include <NGIN/Common/Types/String.hpp>
#include <NGIN/Logging/LogLevel.hpp>

#include <source_location>

namespace NGIN::Logging
{
    /// @brief Interface for log formatters
    /// @todo Add documentation
    class IFormatter
    {
    public:
        virtual String Format(LogLevel level, const std::source_location& source, const String& message) = 0;
    };
}// namespace NGIN::Logging