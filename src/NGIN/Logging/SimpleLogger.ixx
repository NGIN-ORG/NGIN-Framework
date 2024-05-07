

export module NGIN.Logging:SimpleLogger;
export import std;

import :ILogger;
import :ISink;
import :LogLevel;

import NGIN.Containers;
import NGIN.Memory;

namespace NGIN::Logging
{
    /// @class SimpleLogger
    /// @brief A simple logger implementation.
    /// @tparam FormatterType The type of the formatter to use for log messages.
    export template<typename FormatterType>
    class SimpleLogger final : public ILogger
    {
    public:
        /// @brief Initializes the logger.
        /// @details This should be called before any logging is done.
        void Initialize() override
        {
            Log(LogLevel::TRACE, "SimpleLogger initialized.", std::source_location::current());
            for (const auto& sink: sinks)
            {
                sink->Initialize();
            }
        }

        void Shutdown() override
        {
            Log(LogLevel::INFO, "SimpleLogger shutting down.", std::source_location::current());
            Flush();
            for (const auto& sink: sinks)
            {
                sink->Shutdown();
            }
        }

        void Flush() override
        {
            Log(LogLevel::TRACE, "SimpleLogger flushing.", std::source_location::current());
            for (const auto& sink: sinks)
            {
                sink->Flush();
            }
        }

        /// @brief Adds a sink to the logger.
        /// @tparam T The type of the sink to add.
        /// @tparam Args The types of the arguments to pass to the sink's constructor.
        /// @param args The arguments to pass to the sink's constructor.
        /// @return A reference to this logger.
        template<typename T, typename... Args>
        SimpleLogger<FormatterType>& AddSink(Args&&... args)
        {
            sinks.emplace_back(CreateScope<T>(std::forward<Args>(args)...));
            return *this;
        }
        /// @brief Forwards a log message to all sinks.
        /// @param level The level of the log message.
        /// @param message The message to log.
        /// @param source The source location of the log message.
        void Log(const LogLevel level, const String& message, const std::source_location& source = std::source_location::current()) override
        {
            for (const auto& sink: sinks)
            {
                sink->Log(level, formatter.Format(level, message, source));
            }
        }
    protected:
        FormatterType formatter = {};
        Vector<Scope<ISink>> sinks = {};
    };



}// namespace NGIN::Logging
