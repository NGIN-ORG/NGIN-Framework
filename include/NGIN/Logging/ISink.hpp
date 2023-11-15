#pragma once
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Common/Types.hpp>
#include <NGIN/Logging/Defines.hpp>

namespace NGIN::Logging
{
    /// @brief Interface for a logging sink.
    /// @details A sink is a class that receives and proccesses log messages.
    NGIN_API class ISink
    {
    public:
        virtual ~ISink() = default;

        virtual Bool Initialize() = 0;

        virtual void Shutdown() = 0;

        virtual void Log(eLogLevel level, const String& message) = 0;

        virtual void Flush() = 0;
    };
}// namespace NGIN::Logging