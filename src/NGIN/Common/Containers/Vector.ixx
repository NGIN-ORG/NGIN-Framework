module;

#include <vector>

export module NGIN.Common.Containers:Vector;

namespace NGIN
{
	export template<typename T>
	using Vector = std::vector<T>;
}