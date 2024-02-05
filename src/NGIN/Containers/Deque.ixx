
export module NGIN.Containers:Deque;
import std;
namespace NGIN
{
    export template<typename T>
    using Deque = std::deque<T>;
}