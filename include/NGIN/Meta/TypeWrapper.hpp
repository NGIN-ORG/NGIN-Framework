#pragma once

#include <NGIN/Defines.hpp>

namespace NGIN::Meta
{
    /// @brief  A wrapper for a type(s)
    /// @tparam ...Ts The type(s) to wrap
    template<typename... Ts>
    struct TypeWrapper {};
}