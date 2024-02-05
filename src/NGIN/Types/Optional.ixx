

export module NGIN.Types:Optional;
import std;

export namespace NGIN
{
    template <typename T>
    using Optional = std::optional<T>;

}// namespace NGIN