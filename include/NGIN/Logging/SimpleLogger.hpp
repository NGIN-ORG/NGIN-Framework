#pragma once

#include <NGIN/Common/Containers/Vector.hpp>
#include <NGIN/Common/Memory/Scope.hpp>
#include <NGIN/Logging/ILogger.hpp>
#include <NGIN/Logging/ISink.hpp>

namespace NGIN::Logging
{
    template<typename Formatter>
    class SimpleLogger : public ILogger
    {
    public:
        void Initialize() override;

        void Shutdown() override;

        void Flush() override;

        template<typename T, typename... Args>
        SimpleLogger<Formatter>& AddSink(Args&&... args);

    protected:
        void LogInternal(eLogLevel level, const std::source_location& source, const String& message) override;

        Formatter formatter = {};
        Vector<Scope<ISink>> sinks = {};
    };

    template<typename Formatter>
    void SimpleLogger<Formatter>::Initialize()
    {
        LogInternal(eLogLevel::Info, std::source_location::current(), "SimpleLogger initialized.");
        for (auto& sink: sinks)
        {
            sink->Initialize();
        }
    }

    template<typename Formatter>
    void SimpleLogger<Formatter>::Shutdown()
    {
        LogInternal(eLogLevel::Info, std::source_location::current(), "SimpleLogger shutting down.");
        Flush();
        for (auto& sink: sinks)
        {
            sink->Shutdown();
        }
    }

    template<typename Formatter>
    void SimpleLogger<Formatter>::Flush()
    {
        LogInternal(eLogLevel::Info, std::source_location::current(), "SimpleLogger flushing.");
        for (auto& sink: sinks)
        {
            sink->Flush();
        }
    }

    template<typename Formatter>
    void SimpleLogger<Formatter>::LogInternal(eLogLevel level, const std::source_location& source, const String& message)
    {
        for (auto& sink: sinks)
        {
            sink->Log(level, formatter.Format(level, source, message));
        }
    }

    template<typename Formatter>
    template<typename T, typename... Args>
    SimpleLogger<Formatter>& SimpleLogger<Formatter>::AddSink(Args&&... args)
    {
        sinks.emplace_back(CreateScope<T>(std::forward<Args>(args)...));
        return *this;
    }
}// namespace NGIN::Logging