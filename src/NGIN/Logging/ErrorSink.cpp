#include <NGIN/Common/Containers/Deque.hpp>
#include <NGIN/Common/Types/String.hpp>
#include <NGIN/Logging/ErrorSink.hpp>

extern NGIN::Deque<NGIN::String> errorLog;

namespace NGIN::Logging
{
    Bool ErrorSink::Initialize()
    {
        return true;
    }

    void ErrorSink::Shutdown()
    {
    }

    void ErrorSink::Log(eLogLevel level, const String& message)
    {
        errorLog.push_back(message);
    }

    void ErrorSink::Flush()
    {
    }
}// namespace NGIN::Logging
