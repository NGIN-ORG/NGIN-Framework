#pragma once

#include <NGIN/Defines.hpp>
#include <NGIN/Logging/ISink.hpp>
#include <iostream>

namespace NGIN::Logging
{
    class ConsoleSink : public ISink
    {
    public:
        void Initialize() override;

        void Shutdown() override;

        void Log(Entry message) override;

        void Flush() override;

    private:
        Bool isTerminal = false;

        void SetColor(eLogLevel level);
        void ResetColor();
    };
}// namespace NGIN::Logging