#pragma once
#include <NGIN/Common/Defines.hpp>
#include <array>
namespace NGIN
{
    template<typename T, size_t N>
    using Array = std::array<T, N>;
}