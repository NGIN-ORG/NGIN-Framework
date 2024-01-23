module;

#include <deque>

export module NGIN.Common.Containers:Deque;

namespace NGIN
{
    export template<typename T>
    using Deque = std::deque<T>;
}