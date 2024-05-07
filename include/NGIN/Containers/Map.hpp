#pragma once
#include <NGIN/Common/Defines.hpp>
#include <map>
namespace NGIN
{
    template<typename Key, typename Value>
    using Map = std::map<Key, Value>;
}