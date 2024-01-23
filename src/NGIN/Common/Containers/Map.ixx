module;

#include <map>

export module NGIN.Common.Containers:Map;

namespace NGIN
{
    export template<typename Key, typename Value>
    using Map = std::map<Key, Value>;
}