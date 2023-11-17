#pragma once

#include <NGIN/Common/Defines.hpp>
#include <NGIN/Common/Types.hpp>
#include <NGIN/Logging/eLogLevel.hpp>
#include <NGIN/Util/Format.hpp>

#include <source_location>

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

        template<typename... Args>
        void Log(eLogLevel level, const std::source_location& source, const String& message, Args&&... args);

    protected:
        virtual void LogInternal(eLogLevel level, const std::source_location& source, const String& message) = 0;
    };


    template<typename... Args>
    void ILogger::Log(eLogLevel level, const std::source_location& source, const String& message, Args&&... args)
    {
        LogInternal(level, source, Util::RuntimeFormat(message, std::forward<Args>(args)...));
    }


}// namespace NGIN::Logging
#ifndef NGIN_DIST
#define NGIN_LOG (logger, level, message, ...) logger.Log(level, ::std::source_location::current(), message, ##__VA_ARGS__)
#define NGIN_LOG_TRACE (logger, message, ...) logger.Log(::NGIN::Logging::Trace, ::std::source_location::current(), message, ##__VA_ARGS__)
#define NGIN_LOG_INFO (logger, message, ...) logger.Log(::NGIN::Logging::eLogLevel::Info, ::std::source_location::current(), message, ##__VA_ARGS__)
#define NGIN_LOG_DEBUG (logger, message, ...) logger.Log(::NGIN::Logging::eLogLevel::Debug, ::std::source_location::current(), message, ##__VA_ARGS__)
#endif
#define NGIN_LOG_WARNING (logger, message, ...) logger.Log(::NGIN::Logging::eLogLevel::Warning, ::std::source_location::current(), message, ##__VA_ARGS__)
#define NGIN_LOG_ERROR (logger, message, ...) logger.Log(::NGIN::Logging::eLogLevel::Error, ::std::source_location::current(), message, ##__VA_ARGS__)
#define NGIN_LOG_CRITICAL (logger, message, ...) logger.Log(::NGIN::Logging::eLogLevel::Critical, ::std::source_location::current(), message, ##__VA_ARGS__)
