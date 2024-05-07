#pragma once
#include <NGIN/Common/Defines.hpp>
#include <string>
#include <SIMDString.h>
#include <NGIN/Memory/FallbackAllocator.hpp>
#include <NGIN/Memory/FreeListAllocator.hpp>
#include <NGIN/Memory/Mallocator.hpp>
#include <NGIN/Memory/STLAllocator.hpp>

namespace NGIN
{
    /// @brief A type alias for the STL complient SIMDString.
    NGIN_API using String = SIMDString<char, 64>;
    /// @brief A type alias for a string with 16-bit characters.
    NGIN_API using String16 = std::basic_string<Char16>;
    /// @brief A type alias for a string with 32-bit characters.
    NGIN_API using String32 = std::basic_string<Char32>;
    /// @brief A type alias for a string with the wide character type.
    NGIN_API using WString = std::basic_string<WChar>;

    // Forward declaration to handle different types
    template <typename T>
    String ToString(const T& value); // For lvalues

    template <typename T>
    String ToString(T&& value); // For rvalues, leveraging forwarding references

    /// @brief Converts a type const T& to a string.
    /// Needs to be specialized for custom types.
    /// Default implementation uses std::to_string.
    template <typename T>
    String ToString(const T& value)
    {
        return String(std::to_string(value));
    }

    /// @brief Converts a type T&& to a string.
    /// Needs to be specialized for custom types.
    /// Default implementation uses std::to_string.
    template <typename T>
    String ToString(T&& value)
    {
        return String(std::to_string(std::forward<T>(value)));
    }

    template <>
    inline String ToString<String>(const String& value)
    {
        return value; // Direct return for lvalues
    }

    template <>
    inline String ToString<String>(String&& value)
    {
        return std::move(value); // Efficient move for rvalues
    }
} // namespace NGIN
