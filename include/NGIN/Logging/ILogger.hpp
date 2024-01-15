#pragma once

#include <NGIN/Common/Defines.hpp>
#include <NGIN/Common/Types.hpp>
#include <NGIN/Logging/LogLevel.hpp>
#include <NGIN/Util/Format.hpp>

#include <source_location>

namespace NGIN::Logging
{
    /// @class ILogger
    /// @brief Interface for a logger.
    /// @details A logger is a class that receives log messages and sends them to various sinks.
    class NGIN_API ILogger
    {
    public:
        /// @brief Virtual destructor.
        virtual ~ILogger() = default;

        /// @brief Initializes the logger.
        virtual void Initialize() = 0;

        /// @brief Initializes the logger.
        virtual void Shutdown() = 0;

        /// @brief Flushes the logger.
        virtual void Flush() = 0;

        /// @brief Logs a message.
        /// @details
        /// This function formats the message using the provided arguments and then calls LogInternal,
        /// which varies depending on the implementation.
        /// @note This function can be called directly, but it is recommended to use the macros instead.
        /// @tparam Args Types of the additional arguments.
        /// @param level Log level of the message.
        /// @param source Source location of the log message.
        /// @param message Log message.
        /// @param args Additional arguments to format the message.
        template<typename... Args>
        void Log(LogLevel level, const std::source_location& source, const String& message, Args&&... args);

    protected:
        virtual void LogInternal(LogLevel level, const std::source_location& source, const String& message) = 0;
    };


    template<typename... Args>
    void ILogger::Log(LogLevel level, const std::source_location& source, const String& message, Args&&... args)
    {
        LogInternal(level, source, Util::RuntimeFormat(message, std::forward<Args>(args)...));
    }


}// namespace NGIN::Logging

#ifndef NGIN_DIST
/// @def NGIN_LOG
/// @brief Macro for logging messages with variable log level.
#define NGIN_LOG(logger, level, message, ...) logger.Log(level, ::std::source_location::current(), message, ##__VA_ARGS__)

/// @def NGIN_LOG_TRACE
/// @brief Macro for logging trace messages.
#define NGIN_LOG_TRACE(logger, message, ...) logger.Log(::NGIN::Logging::Trace, ::std::source_location::current(), message, ##__VA_ARGS__)

/// @def NGIN_LOG_INFO
/// @brief Macro for logging info messages.
#define NGIN_LOG_INFO(logger, message, ...) logger.Log(::NGIN::Logging::LogLevel::Info, ::std::source_location::current(), message, ##__VA_ARGS__)

/// @def NGIN_LOG_DEBUG
/// @brief Macro for logging debug messages.
#define NGIN_LOG_DEBUG(logger, message, ...) logger.Log(::NGIN::Logging::LogLevel::Debug, ::std::source_location::current(), message, ##__VA_ARGS__)
#else

/// @def NGIN_LOG
/// @brief Macro for logging messages with variable log level.
#define NGIN_LOG(logger, level, message, ...)

/// @def NGIN_LOG_TRACE
/// @brief Macro for logging trace messages.
#define NGIN_LOG_TRACE(logger, message, ...)

/// @def NGIN_LOG_INFO
/// @brief Macro for logging info messages.
#define NGIN_LOG_INFO(logger, message, ...)

/// @def NGIN_LOG_DEBUG
/// @brief Macro for logging debug messages.
#define NGIN_LOG_DEBUG(logger, message, ...)
#endif

/// @def NGIN_LOG_WARNING
/// @brief Macro for logging warning messages.
#define NGIN_LOG_WARNING(logger, message, ...) logger.Log(::NGIN::Logging::LogLevel::Warning, ::std::source_location::current(), message, ##__VA_ARGS__)

/// @def NGIN_LOG_ERROR
/// @brief Macro for logging error messages.
#define NGIN_LOG_ERROR(logger, message, ...) logger.Log(::NGIN::Logging::LogLevel::Error, ::std::source_location::current(), message, ##__VA_ARGS__)

/// @def NGIN_LOG_CRITICAL
/// @brief Macro for logging critical messages.
#define NGIN_LOG_CRITICAL(logger, message, ...) logger.Log(::NGIN::Logging::LogLevel::Critical, ::std::source_location::current(), message, ##__VA_ARGS__)