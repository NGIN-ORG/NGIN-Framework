#pragma once

#include <NGIN/Common/Types.hpp>
#include <NGIN/Logging/ISink.hpp>
#include <NGIN/Logging/LogLevel.hpp>
#include <iostream>

namespace NGIN::Logging
{
    class ErrorSink : public ISink
    {
    public:
        Bool Initialize() override;

        void Shutdown() override;

        void Log(LogLevel level, const String& message) override;

        void Flush() override;

    private:
    };
}// namespace NGIN::Logging