
export module NGIN.Logging:LogLevel;

export import NGIN.Meta;
export import NGIN.Types;
export import NGIN.Containers;
export import std;

namespace NGIN::Logging
{
    export enum class LogLevel : UInt8
    {
        TRACE = 0,
        INFO,
        DEBUG,
        WARNING,
        CRITICAL,
        ERROR,
        CUSTOM0,
        CUSTOM1,
        CUSTOM2,
        CUSTOM3,
        CUSTOM4,
        CUSTOM5,
        CUSTOM6,
        CUSTOM7,
        CUSTOM8,
        CUSTOM9,
        COUNT
    };
}

export template<>
struct NGIN::Meta::EnumTraits<NGIN::Logging::LogLevel>
{
    using EnumType = NGIN::Logging::LogLevel;

    constexpr static std::array<const char*, static_cast<NGIN::Size>(EnumType::COUNT)> names = {"Trace", "Info", "Debug", "Warning", "Critical", "Error"};

    static constexpr std::string_view ToString(EnumType value) { return names[static_cast<size_t>(value)]; }

    static EnumType FromString(const NGIN::String& str)
    {
        for (NGIN::Size i = 0; i < static_cast<NGIN::Size>(EnumType::COUNT); ++i) { if (str == names[i]) return static_cast<EnumType>(i); }
        throw std::invalid_argument("Invalid string for LogLevel");
    }

    static constexpr NGIN::Size Size() { return static_cast<NGIN::Size>(EnumType::COUNT); }
};

/*
    template<>
    struct Meta::EnumTraits<Logging::LogLevel>
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

        static constexpr StringView ToString(const Logging::LogLevel level)
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
                default: { return "Unknown"; }
            }
        }

        static constexpr Logging::LogLevel FromString(const String& name)
        {
            if (name == "Trace") return Logging::LogLevel::Trace;
            if (name == "Info") return Logging::LogLevel::Info;
            if (name == "Debug") return Logging::LogLevel::Debug;
            if (name == "Warning") return Logging::LogLevel::Warning;
            if (name == "Error") return Logging::LogLevel::Error;
            if (name == "Critical") return Logging::LogLevel::Critical;
            if (name.find("CUSTOM") == 0 && name.length() > 6) { if (const int customLevel = std::stoi(name.substr(6).c_str()); customLevel >= 0 && customLevel <= 19) return static_cast<Logging::LogLevel>(customLevel - static_cast<int>(Logging::LogLevel::CUSTOM0)); }
            return Logging::LogLevel::Trace;
        }

        static constexpr Logging::LogLevel MinValue() { return Logging::LogLevel::Trace; }
        static constexpr Logging::LogLevel MaxValue() { return Logging::LogLevel::CUSTOM19; }
    };*/
