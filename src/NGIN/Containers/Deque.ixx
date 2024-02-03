module;

#include <deque>

export module NGIN.Containers:Deque;

namespace NGIN
{
    export template<typename T>
    using Deque = std::deque<T>;
}