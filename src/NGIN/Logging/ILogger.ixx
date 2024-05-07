
export module NGIN.Logging:ILogger;

export import NGIN.Types;
import NGIN.Util;
import :LogLevel;
import std;

namespace NGIN::Logging
{
    /// @class ILogger
    /// @brief This class provides an interface for a logger.
    export class ILogger
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ILogger() = default;

        /// @brief Initializes the logger.
        virtual void Initialize() = 0;

        /// @brief Shuts down the logger and cleans up dynamic resources.
        /// @details This should result in the logger being in an invalid state.
        virtual void Shutdown() = 0;

        /// @brief Flushes any buffered messages.
        virtual void Flush() = 0;

        /// @brief Logs a message.
        /// @param level The verbosity level of the log.
        /// @param message The log message.
        /// @param source The source location. Defaults to the current location.
        virtual void Log(const LogLevel level, const String& message, const std::source_location& source = std::source_location::current()) = 0;
    };
}// namespace NGIN::Logging
