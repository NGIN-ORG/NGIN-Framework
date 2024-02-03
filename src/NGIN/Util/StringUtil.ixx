module;

#include <string>
#include <string_view>

export module NGIN.Util:StringUtil;

export import NGIN.Types;

namespace NGIN::Util
{
    /// @brief Extracts the file name from a given full path string.
    ///
    /// This function takes a std::string_view representing a full path and
    /// finds the file name by searching for the last occurrence of either a
    /// forward or backward slash. It is designed to be cross-platform and
    /// accounts for different directory separator conventions.
    ///
    /// @param fullPath The full path string from which the file name should be extracted.
    /// @return A std::string_view pointing to the start of the file name within fullPath.
    export constexpr StringView ExtractFileName(StringView fullPath)
    {
        const auto lastSlash = fullPath.find_last_of("/\\");
        return (lastSlash != StringView::npos) ? fullPath.substr(lastSlash + 1) : fullPath;
    }

    export enum class AnsiColor {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        WHITE,
        RESET
    };

    export inline constexpr StringView ANSI_RED = "\033[31m";
    export inline constexpr StringView ANSI_GREEN = "\033[32m";
    export inline constexpr StringView ANSI_BLUE = "\033[34m";
    export inline constexpr StringView ANSI_YELLOW = "\033[33m";
    export inline constexpr StringView ANSI_WHITE = "\033[37m";
    export inline constexpr StringView ANSI_RESET = "\033[0m";
    export inline constexpr StringView ANSI_CYAN = "\033[36m";
    export inline constexpr StringView ANSI_MAGENTA = "\033[35m";
    export inline constexpr StringView ANSI_GREY = "\033[90m";

    export String ColorString(StringView str, AnsiColor color)
    {
        StringView color_code;
        switch (color)
        {
            case AnsiColor::RED:
                color_code = ANSI_RED;
                break;
            case AnsiColor::GREEN:
                color_code = ANSI_GREEN;
                break;
            case AnsiColor::BLUE:
                color_code = ANSI_BLUE;
                break;
            case AnsiColor::YELLOW:
                color_code = ANSI_YELLOW;
                break;
            case AnsiColor::WHITE:
                color_code = ANSI_WHITE;
                break;
            case AnsiColor::RESET:
                color_code = ANSI_RESET;
                break;
            default:
                color_code = ANSI_RESET;
                break;
        }
        return String(color_code) + String(str) + "\033[0m";
    }
}// namespace NGIN::Util
