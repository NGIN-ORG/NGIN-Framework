//
// Created by Maximiliam Berggren on 02/03/2024.
//

export module NGIN.IO:Format;

export import NGIN.Types;

export import std;


namespace NGIN::IO
{
    /// <summary>Formats a string at runtime using provided format arguments.</summary>
    /// <note>For compile-time string formatting, see `NGIN::Util::Format` function.</note>
    /// <typeparam name="Args">Types of the arguments used for formatting.</typeparam>
    /// <param name="message">The message string to be formatted.</param>
    /// <param name="args">The arguments to be substituted into the format string.</param>
    /// <returns>The formatted string.</returns>
    /// <example>
    ///   NGIN::StringView msg = "Hello, {}!";
    ///   NGIN::String result = RuntimeFormat(msg, "World");
    ///   // result will be "Hello, World!"
    /// </example>
    export template<typename... Args>
    String RuntimeFormat(String message, Args&&... args)
    {
        return std::vformat(message, std::make_format_args(args...));
    }

    /// <summary>Formats a string at compile-time using provided format arguments.</summary>
    /// <note>For runtime string formatting, see `NGIN::Util::RuntimeFormat` function.</note>
    /// <typeparam name="Args">Types of the arguments used for formatting.</typeparam>
    /// <param name="message">The format string (must be a string literal).</param>
    /// <param name="args">The arguments to be substituted into the format string.</param>
    /// <returns>The formatted string.</returns>
    /// <example>
    ///   constexpr const char* msg = "Hello, {}!";
    ///   NGIN::String result = Format(msg, "World");
    ///   // result will be "Hello, World!"
    /// </example>
    export template<typename... Args>
    String Format(std::format_string<Args...> message, Args&&... args)
    {
        return String(std::format(message, std::forward<Args>(args)...).c_str());
    }


}// namespace NGIN::IO
