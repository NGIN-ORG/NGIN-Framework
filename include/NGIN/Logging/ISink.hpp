#pragma once
#include <NGIN/Defines.hpp>
#include <NGIN/Logging/Defines.hpp>

namespace NGIN::Logging
{
    /// @brief Interface for a logging sink.
    /// @details A sink is a class that receives and proccesses log messages.
    class ISink
    {
    public:
        virtual void Log(const std::string& message, eLogLevel level) = 0;
    };
}