#pragma once

#include <NGIN/Defines.hpp>

namespace NGIN::Logging
{
    /// @brief Interface for a logger.
    /// @details A logger is a class that receives log messages and sends them to sinks.
    class NGIN_API ILogger
    {
    public:
        virtual ~ILogger() = default;

        virtual void Initialize() = 0;

        virtual void Shutdown() = 0;

        virtual void Flush() = 0;

        template <typename... Args>
        void Log(const String& message, Args&&... args)

    protected:
        virtual void LogInternal(const String& message) = 0;

        
    };
}