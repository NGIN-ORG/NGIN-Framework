
export module NGIN.Logging:SimpleFormatter;
import std;


import :IFormatter;
import :LogLevel;
import NGIN.Util;
export import NGIN.Types;




namespace NGIN::Logging
{
    export class SimpleFormatter : public IFormatter
    {
    public:
        String Format(LogLevel level, const String& message, const std::source_location& source = std::source_location::current()) override
        {
            String color;
            switch (level)
            {
                case LogLevel::Trace:
                    color = Util::ANSI_GREY;
                    break;
                case LogLevel::Info:
                    color = Util::ANSI_WHITE;
                    break;
                case LogLevel::Warning:
                    color = Util::ANSI_YELLOW;
                    break;
                case LogLevel::Error:
                    color = Util::ANSI_RED;
                    break;
                case LogLevel::Critical:
                    color = Util::ANSI_RED;
                    break;
                case LogLevel::Debug:
                    color = Util::ANSI_CYAN;
                    break;
                default:
                    color = Util::ANSI_RESET;
                    break;
            }
            // Use the formatted time string with std::format
            return Util::Format("{}({}) [{}:{} | {}]\n{}{}",
                                color,
                                Util::GetCurrentFormattedTime(),
                                Util::ExtractFileName(source.file_name()),
                                source.line(),
                                Meta::EnumTraits<LogLevel>::ToString(level),
                                message, Util::ANSI_RESET);
        }
    };

}
