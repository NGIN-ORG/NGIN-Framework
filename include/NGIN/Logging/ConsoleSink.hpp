#pragma once

#include <NGIN/Common/Types.hpp>
#include <NGIN/Logging/ISink.hpp>
#include <NGIN/Logging/LogLevel.hpp>
#include <iostream>

namespace NGIN::Logging
{
    class ConsoleSink : public ISink
    {
    public:
        Bool Initialize() override;

        void Shutdown() override;

        void Log(LogLevel level, const String& message) override;

        void Flush() override;

    private:
        Bool isTerminal = false;

        void SetColor(LogLevel level);
        void ResetColor();
    };
}// namespace NGIN::Logging