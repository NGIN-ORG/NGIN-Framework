module;

#include <utility>
#include <string>

export module NGIN.Logging:SimpleLogger;

import :ILogger;
import :ISink;
import NGIN.Containers;
import NGIN.Memory;

namespace NGIN::Logging
{
    export template<typename Formatter>
    class SimpleLogger final : public ILogger
    {
    public:
        Void Initialize() override;

        Void Shutdown() override;

        Void Flush() override;

        template <typename T, typename... Args>
        SimpleLogger<Formatter>& AddSink(Args&&... args);
    protected:
        Void LogInternal(LogLevel level, const String& message, const std::source_location& source) override;

        Formatter formatter = {};
        Vector<Scope<ISink>> sinks = {};

    };

    template<typename Formatter>
    Void SimpleLogger<Formatter>::Initialize()
    {
        LogInternal(LogLevel::Trace, "SimpleLogger initialized.", std::source_location::current());
        for (const auto& sink: sinks)
        {
            sink->Initialize();
        }
    }

    template<typename Formatter>
    Void SimpleLogger<Formatter>::Shutdown()
    {
        LogInternal(LogLevel::Info, "SimpleLogger shutting down.", std::source_location::current());
        Flush();
        for (const auto& sink: sinks)
        {
            sink->Shutdown();
        }
    }

    template<typename Formatter>
    Void SimpleLogger<Formatter>::Flush()
    {
        LogInternal(LogLevel::Trace, "SimpleLogger flushing.", std::source_location::current());
        for (const auto& sink: sinks)
        {
            sink->Flush();
        }
    }

    
    template<typename Formatter>
    template<typename T, typename... Args>
    SimpleLogger<Formatter>& SimpleLogger<Formatter>::AddSink(Args&&... args)
    {
        sinks.emplace_back(CreateScope<T>(std::forward<Args>(args)...));
        return *this;
    }

    template<typename Formatter>
    Void SimpleLogger<Formatter>::LogInternal(LogLevel level, const String& message, const std::source_location& source)
    {
        for (const auto& sink: sinks)
        {
            sink->Log(level, formatter.Format(level, message, source));
        }
    }
}
