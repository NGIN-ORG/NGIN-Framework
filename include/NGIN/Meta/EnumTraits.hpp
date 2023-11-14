#pragma once

#include <type_traits>


namespace NGIN::Meta
{
    template<typename T>
    struct EnumTraits
    {
        // Use std::is_enum_v<T> in the static assertion
        static_assert(std::is_enum_v<T> && !std::is_enum_v<T>,
                      "EnumTraits specialization is required for this enum type.");
    };
}// namespace NGIN::Meta