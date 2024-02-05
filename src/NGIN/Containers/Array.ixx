
export module NGIN.Containers:Array;
import std;

namespace NGIN
{
    export template<typename T, size_t N>
    using Array = std::array<T, N>;
}