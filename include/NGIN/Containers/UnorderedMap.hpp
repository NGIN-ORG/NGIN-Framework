#pragma once
#include <NGIN/Common/Defines.hpp>
#include <unordered_map>

namespace NGIN
{
    template<typename Key, typename Value>
    using UnorderedMap = std::unordered_map<Key, Value>;
}