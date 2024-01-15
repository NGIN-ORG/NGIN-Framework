#pragma once
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Common/Types.hpp>
#include <NGIN/Logging/LogLevel.hpp>

namespace NGIN::Logging
{
    /// @brief Interface for a logging sink.
    /// @details A sink is a class that receives and processes log messages.
    NGIN_API class ISink
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ISink() = default;

        /// @brief Initializes the sink.
        /// @return Boolean indicating success or failure of initialization.
        virtual Bool Initialize() = 0;

        /// @brief Shuts down the sink.
        virtual void Shutdown() = 0;

        /// @brief Logs a message at a specific log level.
        /// @param level The level of the log.
        /// @param message The message to log.
        virtual void Log(LogLevel level, const String& message) = 0;

        /// @brief Flushes any buffered log messages.
        virtual void Flush() = 0;
    };
}// namespace NGIN::Logging