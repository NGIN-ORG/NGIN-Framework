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


        enum class eLogLevel
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
    struct NGIN::Meta::EnumTraits<Logging::eLogLevel>
    {
        static constexpr Array<Logging::eLogLevel, 26> values = {
                Logging::eLogLevel::Trace, Logging::eLogLevel::Info, Logging::eLogLevel::Debug,
                Logging::eLogLevel::Warning, Logging::eLogLevel::Error, Logging::eLogLevel::Critical,
                Logging::eLogLevel::CUSTOM0, Logging::eLogLevel::CUSTOM1, Logging::eLogLevel::CUSTOM2,
                Logging::eLogLevel::CUSTOM3, Logging::eLogLevel::CUSTOM4, Logging::eLogLevel::CUSTOM5,
                Logging::eLogLevel::CUSTOM6, Logging::eLogLevel::CUSTOM7, Logging::eLogLevel::CUSTOM8,
                Logging::eLogLevel::CUSTOM9, Logging::eLogLevel::CUSTOM10, Logging::eLogLevel::CUSTOM11,
                Logging::eLogLevel::CUSTOM12, Logging::eLogLevel::CUSTOM13, Logging::eLogLevel::CUSTOM14,
                Logging::eLogLevel::CUSTOM15, Logging::eLogLevel::CUSTOM16, Logging::eLogLevel::CUSTOM17,
                Logging::eLogLevel::CUSTOM18, Logging::eLogLevel::CUSTOM19};

        static constexpr Size size = values.size();

        static constexpr String GetName() { return "Logging::eLogLevel"; }

        static constexpr String ToString(Logging::eLogLevel level)
        {
            switch (level)
            {
                case Logging::eLogLevel::Trace:
                    return "Trace";
                case Logging::eLogLevel::Info:
                    return "Info";
                case Logging::eLogLevel::Debug:
                    return "Debug";
                case Logging::eLogLevel::Warning:
                    return "Warning";
                case Logging::eLogLevel::Error:
                    return "Error";
                case Logging::eLogLevel::Critical:
                    return "Critical";
                // Handle custom log levels
                default: {
                    if (level >= Logging::eLogLevel::CUSTOM0 && level <= Logging::eLogLevel::CUSTOM19)
                    {
                        return "CUSTOM" + std::to_string(static_cast<int>(level) - static_cast<int>(Logging::eLogLevel::CUSTOM0));
                    }
                    return "Unknown";
                }
            }
        }
        static constexpr Logging::eLogLevel FromString(const String& name)
        {
            if (name == "Trace") return Logging::eLogLevel::Trace;
            if (name == "Info") return Logging::eLogLevel::Info;
            // ... similar checks for other levels ...
            if (name.find("CUSTOM") == 0 && name.length() > 6)
            {
                int customLevel = std::stoi(name.substr(6));
                if (customLevel >= 0 && customLevel <= 19)
                    return static_cast<Logging::eLogLevel>(customLevel - static_cast<int>(Logging::eLogLevel::CUSTOM0));
            }
            return Logging::eLogLevel::Trace;
        }
        static constexpr Logging::eLogLevel minValue() { return Logging::eLogLevel::Trace; }
        static constexpr Logging::eLogLevel maxValue() { return Logging::eLogLevel::CUSTOM19; }
    };

}// namespace NGIN