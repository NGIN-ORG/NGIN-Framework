#pragma once
#include <NGIN/Common/Defines.hpp>
#include <NGIN/Types/String.hpp>
#include <format>


namespace NGIN::IO
{
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
    template <typename... Args>
    String Format(std::format_string<Args...> message, Args&&... args)
    {
        return String(std::move(std::format(message, std::forward<Args>(args)...)));
    }

    /// <summary>Formats a string at runtime using provided format arguments.</summary>
    /// <note>For compile-time string formatting, see `NGIN::Util::Format` function.</note>
    /// <typeparam name="Args">Types of the arguments used for formatting.</typeparam>
    /// <param name="message">The string to be formatted.</param>
    /// <param name="args">The arguments to be substituted into the string.</param>
    /// <returns>The formatted string.</returns>
    /// <example>
    ///   NGIN::StringView msg = "Hello, {}!";
    ///   NGIN::String result = RuntimeFormat(msg, "World");
    ///   // result will be "Hello, World!"
    /// </example>
    template <typename... Args>
    String RuntimeFormat(const std::string_view message, Args&&... args)
    {
        return String(std::move(std::vformat(message, std::make_format_args(args...))));
    }


space NGIN::IO
