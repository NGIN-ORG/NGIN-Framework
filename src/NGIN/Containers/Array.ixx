module;

#include <array>

export module NGIN.Containers:Array;

namespace NGIN
{
    export template<typename T, size_t N>
    using Array = std::array<T, N>;
}