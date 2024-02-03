module;

#include <optional>


export module NGIN.Types:Optional;

export namespace NGIN
{
    template <typename T>
    using Optional = std::optional<T>;

}// namespace NGIN