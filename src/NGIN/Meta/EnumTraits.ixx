module;



export module NGIN.Meta:EnumTraits;

import std;

export namespace NGIN::Meta
{
    
    template<typename T>
    struct EnumTraits
    {
        // Creates a nice error message when template specialization is missing.
        static_assert(std::is_enum_v<T> && !std::is_enum_v<T>,
                      "EnumTraits specialization is required for this enum type.");
    };
}