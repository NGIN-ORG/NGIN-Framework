
export module NGIN.Types:Primitives;
export import std;
namespace NGIN
{
    /// TODO: Add documentation
    export using UInt64 = std::uint64_t;
    export using UInt32 = std::uint32_t;
    export using UInt16 = std::uint16_t;
    export using UInt8 = std::uint8_t;

    export using Int64 = std::int64_t;
    export using Int32 = std::int32_t;
    export using Int16 = std::int16_t;
    export using Int8 = std::int8_t;

    export using Byte = std::byte;

    export using F32 = float;
    export using F64 = double;

    export using Size = std::size_t;
    export using IntPtr = std::intptr_t;
    export using UIntPtr = std::uintptr_t;

    export using Char = char;
    export using WChar = wchar_t;
    export using Char8 = char8_t;
    export using Char16 = char16_t;
    export using Char32 = char32_t;

    export using Int = int;
    export using UInt = unsigned int;

    export using Long = long;
    export using ULong = unsigned long;
}// namespace NGIN