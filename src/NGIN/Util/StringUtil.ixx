
export module NGIN.Util:StringUtil;

export import NGIN.Types;
export import std;

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
    export constexpr std::string_view ExtractFileName(std::string_view fullPath)
    {
        const auto lastSlash = fullPath.find_last_of("/\\");
        return (lastSlash != std::string_view::npos) ? fullPath.substr(lastSlash + 1) : fullPath;
    }

    export enum class AnsiColor {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        WHITE,
        GREY,
        CYAN,
        MAGENTA,
        RESET
    };


export constexpr std::string_view GetAnsiCode(AnsiColor color)
    {
        switch (color)
        {
            case AnsiColor::RED:
                return "\033[31m";
            case AnsiColor::GREEN:
                return "\033[32m";
            case AnsiColor::BLUE:
                return "\033[34m";
            case AnsiColor::YELLOW:
                return "\033[33m";
            case AnsiColor::WHITE:
                return "\033[37m";
            case AnsiColor::GREY:
                return "\033[90m";
            case AnsiColor::CYAN:
                return "\033[36m";
            case AnsiColor::MAGENTA:
                return "\033[35m";
            case AnsiColor::RESET:
                return "\033[0m";
            default:
                return "\033[0m";
        }
    }

    export String ColorString(std::string_view str, AnsiColor color)
    {
        auto colorCode = GetAnsiCode(color);
        return std::string(colorCode) + std::string(str) + "\033[0m";
    }
}// namespace NGIN::Util
