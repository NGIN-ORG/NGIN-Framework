module;

#include <map>

export module NGIN.Containers:Map;

namespace NGIN
{
    export template<typename Key, typename Value>
    using Map = std::map<Key, Value>;
}