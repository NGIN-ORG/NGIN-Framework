
export module NGIN.Containers:Map;
import std;

namespace NGIN
{
    export template<typename Key, typename Value>
    using Map = std::map<Key, Value>;
}