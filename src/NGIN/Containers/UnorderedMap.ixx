module;

#include <unordered_map>

export module NGIN.Containers:UnorderedMap;

namespace NGIN
{
    export template<typename Key, typename Value>
    using UnorderedMap = std::unordered_map<Key, Value>;
}