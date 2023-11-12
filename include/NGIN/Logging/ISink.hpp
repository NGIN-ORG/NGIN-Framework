#pragma once
#include <NGIN/Defines.hpp>
#include <NGIN/Logging/Defines.hpp>

namespace NGIN::Logging
{
    /// @brief Interface for a logging sink.
    /// @details A sink is a class that receives and proccesses log messages.
    class NGIN_API ISink
    {
    public:
        virtual ~ISink() = default;

        virtual void Initialize() = 0;

        virtual void Shutdown() = 0;

        virtual void LogHeader() = 0;

        virtual void Log(Entry message) = 0;

        virtual void Flush() = 0;
    };
}// namespace NGIN::Logging