#pragma once
#include <NGIN/Common/Defines.hpp>
#include <cstddef>
#include <cstdint>

namespace NGIN
{
    /// @brief Represents a 64-bit unsigned integer.
    NGIN_API using UInt64 = std::uint64_t;
    /// @brief Represents a 32-bit unsigned integer.
    NGIN_API using UInt32 = std::uint32_t;
    /// @brief Represents a 16-bit unsigned integer.
    NGIN_API using UInt16 = std::uint16_t;
    /// @brief Represents an 8-bit unsigned integer.
    NGIN_API using UInt8 = std::uint8_t;

    /// @brief Represents a 64-bit signed integer.
    NGIN_API using Int64 = std::int64_t;
    /// @brief Represents a 32-bit signed integer.
    NGIN_API using Int32 = std::int32_t;
    /// @brief Represents a 16-bit signed integer.
    NGIN_API using Int16 = std::int16_t;
    /// @brief Represents an 8-bit signed integer.
    NGIN_API using Int8 = std::int8_t;

    /// @brief Represents a byte.
    NGIN_API using Byte = std::byte;

    /// @brief Represents a 32-bit floating point number.
    NGIN_API using F32 = float;
    /// @brief Represents a 64-bit floating point number.
    NGIN_API using F64 = double;

    /// @brief Represents the size type, used for indexing. 64-bit on most systems.
    NGIN_API using Size = std::size_t;
    /// @brief Represents a signed integer type that is large enought to hold a pointer.
    NGIN_API using IntPtr = std::intptr_t;
    /// @brief Represents an unsigned integer type that is large enought to hold a pointer.
    NGIN_API using UIntPtr = std::uintptr_t;

    /// @brief Represents a character type, usually 8-bit.
    NGIN_API using Char = char;
    /// @brief Represents a wide character type, depends on the platform. Most probably it wil either be 16-bit or 32-bit.
    NGIN_API using WChar = wchar_t;
    /// @brief Represents a 8-bit character type.
    NGIN_API using Char8 = char8_t;
    /// @brief Represents a 16-bit character type.
    NGIN_API using Char16 = char16_t;
    /// @brief Represents a 32-bit character type.
    NGIN_API using Char32 = char32_t;

    /// @brief Represents a signed integer.
    NGIN_API using Int = int;
    /// @brief Represents an unsigned integer.
    NGIN_API using UInt = unsigned int;

    /// @brief Represents a long signed integer.
    NGIN_API using Long = long;
    /// @brief Represents a long unsigned integer.
    NGIN_API using ULong = unsigned long;
} // namespace NGIN
