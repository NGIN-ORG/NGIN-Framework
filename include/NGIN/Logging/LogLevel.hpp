#pragma once
#include <NGIN/Common/Containers/Array.hpp>
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Common/Types.hpp>

#include <NGIN/Meta/EnumTraits.hpp>
#include <NGIN/Time/Defines.hpp>
#include <iostream>
namespace NGIN
{
    namespace Logging
    {


        enum class LogLevel
        {
            Trace = 0,///< Trace-level log, usually very detailed.
            Info,     ///< Informational messages, general knowledge about system operations.
            Debug,    ///< Used during debugging to log additional info.
            Warning,  ///< Represents warnings that aren't critical but might indicate potential issues.
            Error,    ///< Represents errors that aren't fatal but might impact normal operation.
            Critical, ///< Critical errors that might cause the system to terminate.
            CUSTOM0,  ///< Custom log level 0.
            CUSTOM1,  ///< Custom log level 1.
            CUSTOM2,  ///< Custom log level 2.
            CUSTOM3,  ///< Custom log level 3.
            CUSTOM4,  ///< Custom log level 4.
            CUSTOM5,  ///< Custom log level 5.
            CUSTOM6,  ///< Custom log level 6.
            CUSTOM7,  ///< Custom log level 7.
            CUSTOM8,  ///< Custom log level 8.
            CUSTOM9,  ///< Custom log level 9.
            CUSTOM10, ///< Custom log level 10.
            CUSTOM11, ///< Custom log level 11.
            CUSTOM12, ///< Custom log level 12.
            CUSTOM13, ///< Custom log level 13.
            CUSTOM14, ///< Custom log level 14.
            CUSTOM15, ///< Custom log level 15.
            CUSTOM16, ///< Custom log level 16.
            CUSTOM17, ///< Custom log level 17.
            CUSTOM18, ///< Custom log level 18.
            CUSTOM19, ///< Custom log level 19.
        };


    }// namespace Logging

    template<>
    struct NGIN::Meta::EnumTraits<Logging::LogLevel>
    {
        static constexpr Array<Logging::LogLevel, 26> values = {
                Logging::LogLevel::Trace, Logging::LogLevel::Info, Logging::LogLevel::Debug,
                Logging::LogLevel::Warning, Logging::LogLevel::Error, Logging::LogLevel::Critical,
                Logging::LogLevel::CUSTOM0, Logging::LogLevel::CUSTOM1, Logging::LogLevel::CUSTOM2,
                Logging::LogLevel::CUSTOM3, Logging::LogLevel::CUSTOM4, Logging::LogLevel::CUSTOM5,
                Logging::LogLevel::CUSTOM6, Logging::LogLevel::CUSTOM7, Logging::LogLevel::CUSTOM8,
                Logging::LogLevel::CUSTOM9, Logging::LogLevel::CUSTOM10, Logging::LogLevel::CUSTOM11,
                Logging::LogLevel::CUSTOM12, Logging::LogLevel::CUSTOM13, Logging::LogLevel::CUSTOM14,
                Logging::LogLevel::CUSTOM15, Logging::LogLevel::CUSTOM16, Logging::LogLevel::CUSTOM17,
                Logging::LogLevel::CUSTOM18, Logging::LogLevel::CUSTOM19};

        static constexpr Size size = values.size();

        static constexpr String GetName() { return "Logging::LogLevel"; }

        static constexpr String ToString(Logging::LogLevel level)
        {
            switch (level)
            {
                case Logging::LogLevel::Trace:
                    return "Trace";
                case Logging::LogLevel::Info:
                    return "Info";
                case Logging::LogLevel::Debug:
                    return "Debug";
                case Logging::LogLevel::Warning:
                    return "Warning";
                case Logging::LogLevel::Error:
                    return "Error";
                case Logging::LogLevel::Critical:
                    return "Critical";
                // Handle custom log levels
                default: {
                    if (level >= Logging::LogLevel::CUSTOM0 && level <= Logging::LogLevel::CUSTOM19)
                    {
                        return "CUSTOM" + std::to_string(static_cast<int>(level) - static_cast<int>(Logging::LogLevel::CUSTOM0));
                    }
                    return "Unknown";
                }
            }
        }
        static constexpr Logging::LogLevel FromString(const String& name)
        {
            if (name == "Trace") return Logging::LogLevel::Trace;
            if (name == "Info") return Logging::LogLevel::Info;
            // ... similar checks for other levels ...
            if (name.find("CUSTOM") == 0 && name.length() > 6)
            {
                int customLevel = std::stoi(name.substr(6));
                if (customLevel >= 0 && customLevel <= 19)
                    return static_cast<Logging::LogLevel>(customLevel - static_cast<int>(Logging::LogLevel::CUSTOM0));
            }
            return Logging::LogLevel::Trace;
        }
        static constexpr Logging::LogLevel minValue() { return Logging::LogLevel::Trace; }
        static constexpr Logging::LogLevel maxValue() { return Logging::LogLevel::CUSTOM19; }
    };

}// namespace NGIN