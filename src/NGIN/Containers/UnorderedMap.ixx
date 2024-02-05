
export module NGIN.Containers:UnorderedMap;
import std;

namespace NGIN
{
    export template<typename Key, typename Value>
    using UnorderedMap = std::unordered_map<Key, Value>;
}