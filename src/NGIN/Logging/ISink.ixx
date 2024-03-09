export module NGIN.Logging:ISink;

export import NGIN.Types;
import NGIN.Util;
import :LogLevel;

namespace NGIN::Logging
{
    export class ISink
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ISink() = default;

        /// @brief Initializes the sink.
        /// @return Boolean indicating success or failure of initialization.
        virtual bool Initialize() = 0;

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
