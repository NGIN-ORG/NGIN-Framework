
export module NGIN.Logging:SimpleFormatter;
import std;


import :IFormatter;
import :LogLevel;
import NGIN.Util;
import NGIN.IO;
export import NGIN.Types;


namespace NGIN::Logging
{

    export class SimpleFormatter : public IFormatter
    {
    public:
        String Format(LogLevel level,
                      const String& message,
                      const std::source_location& source = std::source_location::current()) override
        {
            Util::AnsiColor color;
            switch (level)
            {
                case LogLevel::Trace:
                    color = Util::AnsiColor::GREY;
                    break;
                case LogLevel::Info:
                    color = Util::AnsiColor::WHITE;
                    break;
                case LogLevel::Warning:
                    color = Util::AnsiColor::YELLOW;
                    break;
                case LogLevel::Error:
                    color = Util::AnsiColor::RED;
                    break;
                case LogLevel::Critical:
                    color = Util::AnsiColor::RED;
                    break;
                case LogLevel::Debug:
                    color = Util::AnsiColor::BLUE;
                    break;
                default:
                    color = Util::AnsiColor::WHITE;
                    break;
            }
            // Use the formatted time string with std::format
            return Util::ColorString(IO::Format("[{}] [{}] [{}:{}]\n{}",
                              Meta::EnumTraits<LogLevel>::ToString(level),
                              Util::GetCurrentFormattedTime(),
                              Util::ExtractFileName(source.file_name()),
                              source.line(),
                              message), color);
        }
    };

}// namespace NGIN::Logging
