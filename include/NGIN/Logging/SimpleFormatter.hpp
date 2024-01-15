#pragma once

#include <NGIN/Logging/IFormatter.hpp>

namespace NGIN::Logging
{
    class SimpleFormatter : public IFormatter
    {
    public:
        String Format(LogLevel level, const std::source_location& source, const String& message) override;
    };
}// namespace NGIN::Logging