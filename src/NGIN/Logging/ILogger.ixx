
export module NGIN.Logging:ILogger;

export import NGIN.Types;
import NGIN.Util;
import :LogLevel;
import std;

namespace NGIN::Logging
{

    /// <summary>Interface for a logger</summary>
    export class ILogger
    {
    public:
        virtual ~ILogger() = default;

        /// <summary>Initializes the logger</summary>
        virtual void Initialize() = 0;

        /// <summary>Shuts down the logger</summary>
        virtual void Shutdown() = 0;

        /// <summary>Flushes the sink, i.e dumps buffered content</summary>
        virtual void Flush() = 0;



        /// <summary>Formats and logs a message. Supports 1 formatting argument </summary>
        /// <remarks>This method has overrides in order to support different number of arguments</remarks>
        /// <param name="level">Verbosity of log</param>
        /// <param name="message">The log message</param>
        /// <param name="source">The source location</param>
        template<typename T>
        inline void Log(const LogLevel level, const String& message, T&& arg1, const std::source_location& source = std::source_location::current())
        {
            LogInternal(level, Util::RuntimeFormat(message, std::forward<T>(arg1)), source);
        }
        /// <summary>Formats and logs a message. Supports 2 formatting argument </summary>
        /// <remarks>This method has overrides in order to support different number of arguments</remarks>
        /// <param name="level">Verbosity of log</param>
        /// <param name="message">The log message</param>
        /// <param name="source">The source location</param>
        template<typename A1, typename  A2>
        inline void Log(const LogLevel level, const String& message, A1&& arg1, A2&& arg2, const std::source_location& source = std::source_location::current())
        {
            LogInternal(level, Util::RuntimeFormat(message, std::forward<A1>(arg1), std::forward<A2>(arg2)), source);
        }
        /// <summary>Formats and logs a message. Supports 3 formatting argument </summary>
        /// <remarks>This method has overrides in order to support different number of arguments</remarks>
        /// <param name="level">Verbosity of log</param>
        /// <param name="message">The log message</param>
        /// <param name="source">The source location</param>
        template<typename A1, typename A2, typename A3>
        inline void Log(const LogLevel level, const String& message, A1&& arg1, A2&& arg2, A3&& arg3, const std::source_location& source = std::source_location::current())
        {
            LogInternal(level, Util::RuntimeFormat(message, std::forward<A1>(arg1), std::forward<A2>(arg2), std::forward<A3>(arg3)), source);
        }
        /// <summary>Formats and logs a message. Supports 4 formatting argument </summary>
        /// <remarks>This method has overrides in order to support different number of arguments</remarks>
        /// <param name="level">Verbosity of log</param>
        /// <param name="message">The log message</param>
        /// <param name="source">The source location</param>
        template<typename A1, typename A2, typename A3, typename A4>
        inline void Log(const LogLevel level, const String& message, A1&& arg1, A2&& arg2, A3&& arg3, A4&& arg4, const std::source_location& source = std::source_location::current())
        {
            LogInternal(level, Util::RuntimeFormat(message, std::forward<A1>(arg1), std::forward<A2>(arg2), std::forward<A3>(arg3), std::forward<A4>(arg4)), source);
        }
        /// <summary>Formats and logs a message</summary>
        /// <remarks>This method has overrides in order to support formatting</remarks>
        /// <param name="level">Verbosity of log</param>
        /// <param name="message">The log message</param>
        /// <param name="source">The source location</param>
        inline void Log(const LogLevel level, const String& message, const std::source_location& source = std::source_location::current())
        {
            LogInternal(level, message, source);
        }

        /// <summary>Formats and logs a message. Supports any number of formatting arguments. </summary>
        /// <remarks>The <c>source</c> parameter has no default value.</remarks>
        /// <param name="args">The formatting arguments</param>
        /// <param name="level">Verbosity of log</param>
        /// <param name="message">The log message</param>
        /// <param name="source">The source location</param>
        /// <typeparam name="Args">The types of the formatting arguments</typeparam>
        template<typename... Args>
        inline void Log(const std::source_location& source, const LogLevel level, const String& message, Args&&... args)
        {
            LogInternal(level, Util::RuntimeFormat(message, std::forward<Args>(args)...), source);
        }

    protected:
        /// <summary>Forwards a log to all sinks owned by this logger</summary>
        /// <param name="level">Verbosity of log</param>
        /// <param name="message">The log message</param>
        /// <param name="source">The source location</param>
        virtual void LogInternal(const LogLevel level, const String& message, const std::source_location& source = std::source_location::current()) = 0;
    };
}



